#include <random>
#include <iostream>
using namespace std;

int main() {
	std::random_device seedgen; // 非确定的均匀随机位生成器
								// 在熵池耗尽之前非常高效
								// 所以用来当种子生成器
								// NOIP 考场最好不用？
    // 这个东西似乎在 32bit 上会寄（生成同样的数据），
    // 但是 win下的 msys2 64bit 没有事情，NOI linux 还没有测试。
	用 time 也行。					

    std::mt19937 Myrand(seedgen()); // 自定义一个 mt19937 类型的生成器

    std::uniform_int_distribution<long long> RangeInt(0, 114514); // 指定整数范围
	std::uniform_real_distribution<long double> RangeReal(0.0, 1919810.0); // 指定实数范围

	cout << Myrand() << endl; // 没有范围,但是 mt19937 是 32 位的，所以会在 int 以内。
	cout << RangeInt(Myrand) << endl; // 有范围的均匀整数
	cout << RangeReal(Myrand) << endl; // 有范围的均匀实数
}
// 还有一个用于 64 位整数版的 mt19937: mt19937_64
