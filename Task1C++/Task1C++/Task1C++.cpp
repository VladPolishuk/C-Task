#include <iostream>
#include <cmath>
using namespace std;
int formula(int x) {
    cin >> x;
    int n = 0;
    unsigned long long fact = 1; // это для факториала, он очень быстро растёт
    double answer = 0;
    double ans = 0;
    double e = pow(10, -6);
    while (ans > e || ans == 0) {
        ans = (pow(x + 3, n)) / fact;
        if (n != 0) {
            fact *= n;
        }
        n++;
        answer += ans;
    }
    return answer;
}
int main()
{
    setlocale(LC_ALL,"rus");
    int x;
    do {
        cout << "Введите значение x: ";
        if ((cin >> x)) {
            cout << "Значение числового ряда для x = " << x << " равно: " << formula(x) << endl;
            break;
        }
        else {
            cout << "Ошибка ввода! Пожалуйста, введите число." << endl;
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    } while (!cin.fail());
    return 0;
}