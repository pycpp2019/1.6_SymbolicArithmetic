#include <iostream>
#include <sstream>

#include <vector>
#include <string>
#include <stack>
#include <functional>
#include <utility>

#include "rng.hh"

#include <Common.h>


static const int ATTEMPTS = 16;

int rand_int(Rng *rng) {
    return (rng->rand_int() % 2001) - 1000;
}

std::pair<ExpressionPtr, int> random_expr(
    Rng *rng, std::stringstream &ss, int max_depth, int depth=0, int *count = nullptr
) {
    double p = double(depth)/(max_depth - 1);
    if (rng->uniform() < p) {
        int n = rand_int(rng);
        ss << "(" << n << ")";
        if (count) { *count += 1; }
        return make_pair(Value(n), n);
    } else {
        char op_sym;
        std::function<int(int, int)> op_fn;
        std::function<ExpressionPtr(ExpressionPtr, ExpressionPtr)> op_expr;
        if (rng->uniform() < 0.5) {
            op_sym = '+';
            op_fn = [](int a, int b) -> int { return a + b; };
            op_expr = Sum;
        } else {
            op_sym = '*';
            op_fn = [](int a, int b) -> int { return a*b; };
            op_expr = Product;
        }

        if (count) { *count += 2; }

        ss << "(";
        std::pair<ExpressionPtr, int> left = random_expr(rng, ss, max_depth, depth + 1, count);
        ss << op_sym;
        std::pair<ExpressionPtr, int> right = random_expr(rng, ss, max_depth, depth + 1, count);
        ss << ")";

        return std::make_pair(
            op_expr(std::move(left.first), std::move(right.first)),
            op_fn(left.second, right.second)
        );
    }
}

int main() {
    std::vector<std::pair<std::string, std::function<bool(Rng*)>>> tests = {
        std::make_pair("a", [](Rng *rng) -> bool {
            for (int i = 0; i < ATTEMPTS; ++i) {
                int n = rand_int(rng);
                ExpressionPtr e = Value(n);
                if (n != e->Evaluate()) {
                    return false;
                }
                std::stringstream ss;
                ss << "(" << n << ")";
                if (ss.str() != e->ToString()) {
                    return false;
                }
            }
            return true;
        }),
        std::make_pair("a+b", [](Rng *rng) -> bool {
            for (int i = 0; i < ATTEMPTS; ++i) {
                int a = rand_int(rng);
                int b = rand_int(rng);
                ExpressionPtr e = Sum(Value(a), Value(b));
                if (a + b != e->Evaluate()) {
                    return false;
                }
                std::stringstream ss;
                ss << "((" << a << ")+(" << b << "))";
                if (ss.str() != e->ToString()) {
                    return false;
                }
            }
            return true;
        }),
        std::make_pair("a*b", [](Rng *rng) -> bool {
            for (int i = 0; i < ATTEMPTS; ++i) {
                int a = rand_int(rng);
                int b = rand_int(rng);
                ExpressionPtr e = Product(Value(a), Value(b));
                if (a*b != e->Evaluate()) {
                    return false;
                }
                std::stringstream ss;
                ss << "((" << a << ")*(" << b << "))";
                if (ss.str() != e->ToString()) {
                    return false;
                }
            }
            return true;
        }),
        std::make_pair("a*(b + c)", [](Rng *rng) -> bool {
            for (int i = 0; i < ATTEMPTS; ++i) {
                int a = rand_int(rng);
                int b = rand_int(rng);
                int c = rand_int(rng);
                ExpressionPtr e = Product(Value(a), Sum(Value(b), Value(c)));
                if (a*(b + c) != e->Evaluate()) {
                    return false;
                }
                std::stringstream ss;
                ss << "((" << a << ")*((" << b << ")+(" << c << ")))";
                if (ss.str() != e->ToString()) {
                    return false;
                }
            }
            return true;
        })
    };

    std::vector<std::pair<int, int>> depths = {
        std::make_pair(10, 4),
        std::make_pair(100, 12),
        std::make_pair(1000, 22),
        std::make_pair(1000000, 55),
    };
    for (std::pair<int, int> dp : depths) {
        std::stringstream ssn;
        ssn << "random ~" << dp.first << " nodes";
        tests.push_back(std::make_pair(ssn.str(), [dp](Rng *rng) -> bool {
            for (int i = 0; i < ATTEMPTS; ++i) {
                std::stringstream ss;
                std::pair<ExpressionPtr, int> p = random_expr(rng, ss, dp.second);
                ExpressionPtr e = std::move(p.first);
                if (p.second != e->Evaluate()) {
                    return false;
                }
                if (ss.str() != e->ToString()) {
                    return false;
                }
            }
            return true;
        }));
    }

    Rng rng(0xDEADBEEF);

    int total = tests.size();
    int failed = 0;
    int counter = 0;

    for (std::pair<std::string, std::function<bool(Rng*)>> &pair : tests) {
        std::cout << "(" << counter << "/" << total << ") ";
        std::cout << pair.first << " ... " << std::flush;

        bool ok;
        try {
            ok = pair.second(&rng);
        } catch (...) {
            ok = false;
            std::cout << "unexpected exception caught" << std::endl;
        }

        if (ok) {
            std::cout << "ok";
        } else {
            failed += 1;
            std::cout << "fail";
        }
        std::cout << std::endl;
        counter += 1;
    }

    int ret = 0;
    std::cout << "result: ";
    if (failed > 0) {
        std::cout << "fail";
        ret = 1;
    } else {
        std::cout << "ok";
    }
    std::cout << ". " << total - failed << " passed, " << failed << " failed." << std::endl;

    /*
    int nt = 256;
    for (int i = 2; i < 20; ++i) {
        double s = 0.0;
        for (int j = 0; j < nt; ++j) {
            std::stringstream ss;
            int count = 0;
            random_expr(&rng, ss, i, 0, &count);
            s += count;
        }
        std::cout << i << ": " << (s/nt) << std::endl;
    }
    */

    return ret;
}
