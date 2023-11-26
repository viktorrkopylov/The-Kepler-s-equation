

#include <iostream>
#include <cmath>
#include <fstream>

# define PI           3.14159265358979323846 

using namespace std;

// Метод итераций

double method_of_iteration(double M, double e, double epsilon = 1e-6)
{
    double E_next;
    double E = M;

    for (int i = 0; i <= 30; ++i)       //цикл для поиска кол-ва действий с вводными данными
    {
        E_next = e * sin(E) + M;        // Обновляем значение E
        if (fabs(E_next - E) < epsilon)
            return E_next;

        E = E_next;                     // Вычисляем новое значение E_next
    }

    return 0;
}

double bisection_method(double M, double e, double eps = 1e-6)
{
    double x = M - 5;                   // отрицательное значение
    double y = M + 5;                   // положительное значение
    double z = 0;

    for (int i = 0; i <= 100; ++i)
    {
        z = (x + y) / 2;                // новая середину отрезка
        if (fabs(y - x) < (2 * eps))
            return z;

        if (((x - e * sin(x) - M) * (y - e * sin(y) - M)) < 0)
        {
            y = z; 
        }
        else
        {
            x = z; 
        }
    }

    return z;
}

double golden_method(double M, double e, double eps= 1e-6)
{
    double x = M - 5;                                           // Любое отрицательное значение
    double y = M + 5;                                           // Любое положительное значение
    double z = 0;
    double phi = (sqrt(5) + 1) / 2;                             // Золотое сечение

    for (int i = 0; i <= 30; ++i)
    {
        z = x + (y - x) / phi;                                  // Вычисляем новую середину отрезка
        if (fabs(y - x) < 2 * eps)
            return z;

        if ((x - e * sin(x) - M) * (y - e * sin(y) - M) < 0)
        {
            y = z;                                              // Обновляем правую границу отрезка
        }
        else
        {
            x = z;                                          // Обновляем левую границу отрезка
        }
    }

    return z;
}

double newton_method(double M, double e, double eps = 1e-6)
{
    double E = M;                                           // начальное приближение

    for (int i = 0; i < 40; ++i)
    {
        double f = E - e * sin(E) - M;                      // значение функции
        double f_der = 1 + e * cos(E);                      // значение производной функции

        E -= f / f_der;                                     // вычисление следующего приближения 

        if (abs(f) < eps)                                   // проверка условия сходимости
        {
            break;
        }
    }

    return abs(E);
}

int main() {
    // начальные параметры орбиты
    setlocale(LC_ALL, "rus");

    double T = 9015;                        // период обращения (в секундах)
    double Ra = 1017000;                    //  радиус апоцентра
    double Rp = 350000;                     //  радиус перицентра 
    double eps = 1e-6;
    double w = 2 * PI / T;                  // средняя угловая скорость 
    double a = (Ra + Rp) / 2;               // большая полуось 
    double e = ((Ra - Rp) / (2 * a));       // эсцентриситет орбиты 0,487929

    
//______________________________________________________ФАЙЛЫ____________________________________________________



    // Создание 1 файла
    ofstream file1;
    file1.open("Method_1.txt");

    // Проверка открытия
    if (!file1.is_open()) {
        cout << "Ошибка открытия файла.";
        return 0;
    }
    else {
        file1 << "t, c\t";
        file1 << "M(t), рад\t";
        file1 << "E(t), рад\t";
        file1 << "Theta(t), рад\t" << endl;
    }
    

    // Вычисление и запись значений аномалий в файл
    for (int t = 0; t <= T; ++t) {
        file1 << t << "\t";

        double M = w * t;                                                            // Средняя аномалия
        double E = newton_method(M, e, eps);                                         // Эксцентрическая аномалия
        double true_anomaly = atan(sqrt((1 + e) / (1 - e)) * tan(E / 2)) * 2;        // Истинная аномалия

        if (true_anomaly < 0)
            true_anomaly += 2 * PI;

        file1 << M << "\t";
        file1 << E << "\t";
        file1 << true_anomaly << endl;
    }

    file1.close();
    cout << "Данные записаны в файл 'Method_1'\n";

    ofstream file2;
    file2.open("Method_2.txt");

    // Проверка успешного открытия файла
    if (!file2.is_open()) {
        cout << "Ошибка открытия файла.";
        return 0;
    }
    else {
        file2 << "t, c\t";
        file2 << "M(t), рад\t";
        file2 << "E(t), рад\t";
        file2 << "Theta(t), рад\t" << endl;
    }


    // запись значений аномалий в файл
    for (int t = 0; t <= T; ++t) {
        file2 << t << "\t";

        double M = w * t; 
        double E = golden_method(M, e, eps);  
        double true_anomaly = atan(sqrt((1 + e) / (1 - e)) * tan(E / 2)) * 2; 

        if (true_anomaly < 0)
            true_anomaly += 2 * PI;

        file2 << M << "\t";
        file2 << E << "\t";
        file2 << true_anomaly << endl;
    }

    file2.close();
    cout << "Данные записаны в файл 'Method_2'\n";

    // файл 3
    ofstream file3;
    file3.open("Method_3.txt");

    // проверка открытия файла 3
    if (!file3.is_open()) {
        cout << "Ошибка открытия файла.";
        return 0;
    }
    else {
        file3 << "t, c\t";
        file3 << "M(t), рад\t";
        file3 << "E(t), рад\t";
        file3 << "Theta(t), рад\t" << endl;
    }

    // вычисление и запись значений аномалий в файл
    for (int t = 0; t <= T; ++t) {
        file3 << t << "\t";

        double M = w * t; 
        double E = bisection_method(M, e, eps);
        double true_anomaly = atan(sqrt((1 + e) / (1 - e)) * tan(E / 2)) * 2; 

        if (true_anomaly < 0)
            true_anomaly += 2 * PI;

        file3 << M << "\t";
        file3 << E << "\t";
        file3 << true_anomaly << endl;
    }

    file3.close();
    cout << "Данные записаны в файл 'Method_3'\n";

    // Создание файла
    ofstream file4;
    file4.open("Method_4.txt");

    // проверка открытия файла 4
    if (!file4.is_open()) {
        cout << "Ошибка открытия файла.";
        return 0;
    }
    else {
        file4 << "t, c\t";
        file4 << "M(t), рад\t";
        file4 << "E(t), рад\t";
        file4 << "Theta(t), рад\t" << endl;
    }

    for (int t = 0; t <= T; ++t) {
        file4 << t << "\t";

        double M = w * t;                                                      
        double E = method_of_iteration(M, e, eps);                              
        double true_anomaly = atan(sqrt((1 + e) / (1 - e)) * tan(E / 2)) * 2;   

        if (true_anomaly < 0)
            true_anomaly += 2 * PI;

        file4 << M << "\t";
        file4 << E << "\t";
        file4 << true_anomaly << endl;
    }

    file4.close();
    cout << "Данные записаны в файл 'Method_4'.\n";

    return 0;
}
