Привет, Хабр!

"https://habr.com/ru/companies/otus/articles/864900/"

Помните, какие времена были? Когда-то мы всерьез возились с time_t и ctime, огребали от структур tm и, если хотели засечь время, то приходилось чудить с difftime() и писать собственный секундомер на костылях.
Вспомнить страшно — в голове сразу всплывают унылые алгоритмы перевода секунд в даты и обратно, а при упоминании часовых поясов хочется плакать.

Слава небесам, пришел std::chrono! С ним управлять временем в коде можно чуть ли не с шиком: точные интервалы, аккуратные преобразования, поддержка календарей и таймзон — все это теперь под рукой и без изнуряющих плясок с бубном.

В этой статье я расскажу как использовать "std::chrono"

1. "Время, пространство и все такое: time_point и duration"

В "std::chrono" есть две фундаментальные сущности:

time_point — конкретная точка на временной шкале (например, сейчас, когда вы читаете эту строчку — std::chrono::steady_clock::now()).

duration — длительность, то бишь промежуток времени (скажем, 42 наносекунды, которые вы потратили на обдумывание предыдущего предложения).

Классический пример, который можно использовать для измерения производительности:

#include <chrono>
#include <iostream>

long Fibonacci(unsigned n)
{
    // Наивно, медленно, но для демонстрации — сойдет.
    return (n < 2) ? n : Fibonacci(n - 1) + Fibonacci(n - 2);
}

int main()
{
    auto start = std::chrono::steady_clock::now();
    auto result = Fibonacci(42);
    auto end = std::chrono::steady_clock::now();

    std::chrono::duration<double> elapsed = end - start;
    std::cout << "Fibonacci(42) = " << result << "\n"
              << "Время выполнения: " << elapsed.count() << " секунд\n";
    return 0;
}

Секунды, наносекунды — все можно. Для замеров производительности всегда можно брать steady_clock.

2. Выбор подходящих часов

"std::chrono" дает нам:

system_clock — завязан на системное время;

steady_clock — монотонный и надежный для измерений интервалов.

high_resolution_clock — чаще всего просто синоним одного из первых, но с максимально доступной точностью.

Для логирования событий по локальному времени, например, запуска сервиса, подходит system_clock. Для замеров скорости кода — steady_clock. Пример логирования:

#include <chrono>
#include <iostream>
#include <iomanip>

int main()
{
    auto now = std::chrono::system_clock::now();
    std::time_t now_c = std::chrono::system_clock::to_time_t(now);
    std::cout << "Сервис стартовал: "
              << std::put_time(std::localtime(&now_c), "%F %T") << "\n";
    return 0;
}
Так можно знать точный момент запуска, без шаманств вокруг strftime().

3. Операции с duration

Есть "duration" с ними можно добавлять или вычитатать промежутки.

Причем C++14 дал литералы: 1s, 500ms, 10us — чтобы не маяться с громоздкими шаблонами.

#include <chrono>
#include <iostream>

int main() {
    using namespace std::chrono_literals;
    auto dur1 = 2s;   // 2 секунды
    auto dur2 = 500ms; // полсекунды
    auto total = dur1 + dur2;
    std::cout << "Суммарное время: "
              << std::chrono::duration<double>(total).count() << " с\n";
    return 0;
}
Все просто: складываем, вычитаем, умножаем, конвертируем.


4. C++20: календари, часовые пояса и прочее

Если раньше мы криво подгоняли время под локальную дату, сейчас можно играться с year_month_day, weekday и прочими прелестями.

Плюс появилась работа с часовыми поясами: zoned_time, current_zone(). Попробуем отобразить текущее время UTC и локальное время:

#include <chrono>
#include <iostream>
#include <format>

int main() {
    using namespace std::chrono;

    auto now_utc = system_clock::now();
    auto now_utc_sec = floor<seconds>(now_utc);

    std::time_t now_c = system_clock::to_time_t(now_utc_sec);
    std::cout << "Сейчас UTC: " << std::put_time(std::gmtime(&now_c), "%F %T") << "\n";

    try {
        auto tz = current_zone();
        zoned_time zt{tz, now_utc};
        std::cout << "Локальное время: "
                  << std::format("{:%F %T %Z}", zt.get_local_time()) << "\n";
    } catch(const std::exception& e) {
        std::cerr << "Ох, не вышло с таймзоной: " << e.what() << "\n";
    }

    return 0;
}
Теперь можно оказаться в любой точке мира, и код будет правильно отображать время.

Нужна дата через 10 дней? Берем year_month_day:

#include <chrono>
#include <iostream>

int main() {
    using namespace std::chrono;

    auto today = floor<days>(system_clock::now());
    year_month_day ymd(today);

    auto future_ymd = ymd + days(10);

    std::cout << "Сегодня: " << (int)ymd.year() << "-"
              << (unsigned)ymd.month() << "-"
              << (unsigned)ymd.day() << "\n";
    std::cout << "Через 10 дней: " << (int)future_ymd.year() << "-"
                << (unsigned)future_ymd.month() << "-"
                << (unsigned)future_ymd.day() << "\n";
    return 0;
}
Так же в C++20 ввели clock_cast, чтобы можно было, условно, превратить system_clock::time_point в steady_clock::time_point. Но тут надо понимать, что не всякая конвертация оправдана или возможна. Если получится — классно, если нет — получите исключение или недоступную фичу.

#include <chrono>
#include <iostream>

int main() {
    using namespace std::chrono;
    auto sys_now = system_clock::now();

    try {
        auto steady_tp = clock_cast<steady_clock>(sys_now);
        std::cout << "Перевод между часами сработал!\n";
        auto diff = steady_clock::now() - steady_tp;
        std::cout << "Разница: "
                  << duration_cast<milliseconds>(diff).count() << " ms\n";
    } catch (...) {
        std::cerr << "Не могу перевести время между часами!\n";
    }

    return 0;
}


5. Примеры применения

Приведу три примера где "std::chrono" действительно хорош:

5.1 Замер задержки при обработке запросов:
Допустим, есть высоконагруженный бэкенд, который обрабатывает внешние HTTP-запросы. Чтобы понять, сколько реально времени тратится на каждый запрос, можно в начале обработчика зафиксировать текущее время, а в конце — снова, затем вывести в лог разницу.

#include <chrono>
#include <iostream>

void handle_request()
{
    using namespace std::chrono;
    auto start = steady_clock::now();

    // ... тут логика обработки запроса ...

    auto end = steady_clock::now();
    auto diff = duration_cast<milliseconds>(end - start).count();
    std::cout << "Request processed in " << diff << " ms\n";
}

5.2 Периодическая отправка метрик и логирование с временными метками:
Часто приходится отправлять метрики о состоянии сервиса в систему мониторинга. С помощью std::chrono можно легко определить период отправки. Например, нужно каждые 5 секунд пушить статистику.

#include <chrono>
#include <thread>
#include <iostream>

void send_metrics()
{
    // Здесь вы готовите данные о нагрузке, памяти и т.д.
    std::cout << "Metrics sent at " << std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()) << "\n";
}

int main()
{
    using namespace std::chrono_literals;
    while (true)
    {
        send_metrics();
        std::this_thread::sleep_for(5s); // Пауза в 5 секунд между отправками
    }
}
Плюс можно добавлять временные метки к каждому сообщению, используя std::put_time и system_clock, чтобы потом смотреть в логах, когда именно что-то отвалилось.


5.3 Расчет дедлайна при работе с задачами и тайм-аутами:

Представим, что есть потокобезопасная очередь задач, и нужно подождать задачу в течение определенного времени. Если она не поступит — вернуть тайм-аут.
std::chrono позволяет задать дедлайн и сравнить текущее время с этим дедлайном:

#include <chrono>
#include <condition_variable>
#include <mutex>
#include <iostream>
#include <queue>

std::queue<int> tasks;
std::mutex m;
std::condition_variable cv;

bool wait_for_task(int& result, std::chrono::milliseconds timeout)
{
    using clock = std::chrono::steady_clock;
    auto deadline = clock::now() + timeout;

    std::unique_lock<std::mutex> lock(m);
    if (cv.wait_until(lock, deadline, []{ return !tasks.empty(); }))
    {
        result = tasks.front();
        tasks.pop();
        return true;
    }
    else
    {
        return false; // Тайм-аут, задача не пришла вовремя
    }
}

int main() {
    int task;
    if (wait_for_task(task, std::chrono::milliseconds(100))) {
        std::cout << "Got task: " << task << "\n";
    } else {
        std::cout << "No task received within 100ms.\n";
    }
    return 0;
}
А на этом у меня все. Если вам захочется больше погрузиться в эту тему, то можно ознакомиться здесь.
"https://en.cppreference.com/w/cpp/header/chrono"
