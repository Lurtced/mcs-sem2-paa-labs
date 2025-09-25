/**
 * Лабораторная работа №2. Массивы объектов, простое наследование, виртуальные
 * функции, применение наследования.
 *
 * В этой работе и далее предполагается, что вы будете использовать классы,
 * написанные в прошлых работах, и дополнять их по необходимости. Эти классы
 * будут называться по имени без дополнительных указаний, что их надо взять из
 * прошлой работы.
 *
 * Предполагается, что новый классы будут созданы по аналогии с предыдущими
 * работами в отдельных файлах, которые будут включены в сборку.
 *
 * При работе с классами - в учебных целях - нельзя пользоваться контейнерами
 * стандартной библиотеки и нужно следовать принципам инкапсуляции.
 */

#include <iostream>
#include "barrel.hpp"
#include "matrix.hpp"
#include "mystring.hpp"
#include "rect.hpp"
#include "textwrapper.hpp"
#include "basefile.hpp"

#define TABLE "ABCDEFGHIJKLMNOPQRSTUVWXYZ123456" // Encoding table
#define TABLE_SIZE 32


int main() {
    std::cout << "test1\n";
    {
        const char *path = "test_rle.txt";
        char original_data[] = "aaaaaaaaaaaaabbbbbbaaaacccc";
        {
            RleFile file(path, "w");
            file.write(original_data, sizeof(original_data) - 1);
        }
        {
            RleFile file(path, "r");
            int bytes;
            char buf[8];
            int offset = 0;
            do {
                bytes = file.read(buf, sizeof(buf));
                std::cout << "read bytes: " << bytes << '\n';
                for (int i = 0; i < bytes; ++i) {
                    if (buf[i] != original_data[offset + i]) {
                        std::cout << "mismatch at " << offset + i << "\n";
                    }
                }
                offset += bytes; 
            } while(bytes != 0);
            if (offset < sizeof(original_data) - 1) {
                std::cout << "read less than file: " << offset << " < " << sizeof(original_data) - 1 << '\n';
            }
        }
    }
    /**
     * Задание 1. Массивы объектов класса.
     */

    /**
     * Задание 1.1. Массив объектов.
     *
     * Объявите и проинициализируйте массив ar из объектов типа MyString.
     * Выведите элементы массива на консоль.
     */

    {
        std::cout << "Task 1.1" << std::endl;
        MyString ar[5] = {"c", "... world...", "..!"};
        for (int i = 0; i < 3; i++) {
            ar[i].print();
        }
    }

    /**
     * Замените размер массива с 3 на 5, не меняя список инициализаторов.
     *
     * Чем были инициализированы последние 2 элемента? Какие значения могут
     * стоять в списке инициализаторов - в вашем случае и в общем случае?
     */
    /*
    The last two elements were initialized with nullptr (default constructor
    written by me).
    In the list of initializers there can be:
    - a string
    - another MyString
    */

    /**
     * Задание 1.2. Массив указателей на объекты.
     *
     * Объявите и проинициализируйте массив arPtr из трех указателей на объекты
     * типа MyString. Выведите элементы массива на консоль.
     */
    
    {
        std::cout << "\nTask 1.2\n";
        MyString str1("Abcd");
        MyString str2("Efgh");
        MyString str3("Ijkl");
        MyString* arPtr[3] = {&str1, &str2, &str3};
        for (int i = 0; i < 3; i++) {
            (*arPtr[i]).print();
        }
    }

    /**
     * Задание 2. Простое наследование. Аргументы конструктора, передаваемые в
     * базовый класс.
     */

    /**
     * Задание 2.1. Базовый класс.
     *
     * Создайте класс BaseFile, который будет реализовывать работу с файлами с
     * помощью стандартных средств C (cstdio).
     *
     * Класс должен иметь 3 конструктора: первый - конструктор по умолчанию,
     * второй должен принимать путь к файлу и параметры для открытия (как в
     * fopen), третий должен принимать готовый указатель FILE*.
     *
     * Считается, что этот класс *обладает* своим ресурсом - открытым файлом.
     * Что должно быть в дестукторе этого класса?
     *
     * Добавьте следующие методы:
     * - bool is_open() - возвращает true, если файл успешно открыт;
     * - bool can_read() - возвращает true, если из файла можно считать данные;
     * - bool can_write() - возвращает true, если в файл можно записать данные;
     * - size_t write_raw(const void *buf, size_t n_bytes) - записывает
     *   указанное количество байт в файл и возвращает количество байт, которое
     *   удалось записать;
     * - size_t read_raw(void *buf, size_t max_bytes) - читает доступные данные
     *   в буфер, но не более указанного количества и возвращает количество
     *   байт, которое удалось считать;
     * - long tell() - возвращает текущий сдвиг файла (см. функцию ftell);
     * - bool seek(long offset) - устанавливает сдвиг файла (см. функцию fseek)
     *   и возвращает true, если операция успешна.
     *
     * Добавьте также методы `read` и `write`, которые в этом классе будут
     * делать буквально то же, что `read_raw` и `write_raw`, они понадобятся нам
     * позже.
     *
     * Проверьте работу этого класса.
     */
    
     {
        std::cout << "\n\n=== BaseFile Test ===" << std::endl;
        const char* testFilePath = "src/basefiletest.txt";
    
        // Test 1: Basic write operations
        {
            std::cout << "\n[Test 1] Writing to file..." << std::endl;
            BaseFile file(testFilePath, "w");
            
            if (!file.is_open()) {
                std::cout << "ERROR: Failed to open file for writing" << std::endl;
                return 1;
            }
    
            const char* data = "Hello, World!";
            size_t bytes_to_write = strlen(data);
            size_t bytes_written = file.write_raw(data, bytes_to_write);
            
            std::cout << "Attempted to write " << bytes_to_write << " bytes" << std::endl;
            std::cout << "Actually wrote " << bytes_written << " bytes" << std::endl;
            
            if (bytes_written != bytes_to_write) {
                std::cout << "WARNING: Incomplete write operation!" << std::endl;
            }
            
            long position = file.tell();
            std::cout << "Current position after write: " << position << std::endl;
            
            if (position != static_cast<long>(bytes_written)) {
                std::cout << "WARNING: File position unexpected!" << std::endl;
            }
        } // File closes here
    
        // Test 2: Reading operations
        {
            std::cout << "\n[Test 2] Reading from file..." << std::endl;
            BaseFile file(testFilePath, "r");
            
            if (!file.is_open()) {
                std::cout << "ERROR: Failed to open file for reading" << std::endl;
                return 1;
            }
    
            // Verify file position at start
            long position = file.tell();
            std::cout << "Initial position: " << position << " (should be 0)" << std::endl;
            
            if (position != 0) {
                std::cout << "WARNING: File not at beginning!" << std::endl;
            }
    
            // Test reading
            char buffer[50];
            size_t bytes_read = file.read_raw(buffer, sizeof(buffer));
            
            std::cout << "Read " << bytes_read << " bytes" << std::endl;
            std::cout << "Content: " << buffer << std::endl;
            
            // Verify position after read
            position = file.tell();
            std::cout << "Position after read: " << position << std::endl;
            
            // Test seeking
            std::cout << "\n[Test 3] Seeking..." << std::endl;
            if (file.seek(7)) {
                std::cout << "Seek to position 7 successful" << std::endl;
                position = file.tell();
                std::cout << "Current position: " << position << std::endl;
                
                // Read from new position
                bytes_read = file.read_raw(buffer, sizeof(buffer));
                std::cout << "Read from position 7: " << buffer << std::endl;
            } else {
                std::cout << "ERROR: Seek failed!" << std::endl;
            }
            
            // Test seeking beyond EOF
            std::cout << "\n[Test 4] Seeking beyond EOF..." << std::endl;
            if (file.seek(1000)) {
                std::cout << "WARNING: Seek beyond EOF succeeded!" << std::endl;
            } else {
                std::cout << "Seek beyond EOF failed" << std::endl;
            }
        }
    
        std::cout << "\n=== End of Tests ===" << std::endl;
    }

    /**
     * Задание 2.2. Производные классы.
     *
     * Производный класс *наследуется* от базового класса и каким-то образом
     * расширяет его функциональность, при это все еще умея все, что умеет
     * базовый класс.
     *
     * Реализуйте следующие производные классы от класса BaseFile. Производные
     * классы нужно унаследовать так, чтобы пользователю были все еще доступны
     * методы базового класса. Каким образом нужно унаследовать класс для этого?
     * Как еще можно унаследовать класс?
     *
     * Производные классы могут располагаться в том же файле, где и базовый
     * класс.
     *
     * В производных классах добавьте необходимые конструкторы, которые будут
     * вызывать конструктор базового класса.
     *
     * Проверьте работу производных классов.
     */
    
    // здесь можно унаследовать класс с ключом доступа public.
    // в некоторых ситуациях может понадобиться private или protected.

    /**
     * Задание 2.2.1. Base32 кодировщик/декодировщик.
     *
     * Создайте производный класс Base32File, который будет проводить при
     * записи кодировку-декодировку данных, по алгоритму, который вы
     * реализовали в лабораторной работе №4 прошлого семестра.
     *
     * Переопределите методы `read` и `write`, которые будут проводить чтение из
     * файла с декодировкой и запись в файл с кодировкой соответственно.
     *
     * Добавьте возможность пользователю передать в конструктор таблицу
     * кодировки, по умолчанию используется таблица "A..Z1..6".
     */
    
    {
        std::cout << "\n\n=== Base32 Test ===" << std::endl;
        const char* testFilePath = "src/base32test.txt";
        const int LENGTH = 256;
        char decodedData[LENGTH];
        size_t decodedSize;

        {
            std::cout << "\n[Test 1] Reading" << std::endl;
            Base32 file(testFilePath, "r", TABLE, TABLE_SIZE);

            decodedSize = file.read(decodedData, LENGTH);
            for (int i = 0; i < decodedSize; i++) {
                std::cout << decodedData[i];
            }
            std::cout << std::endl;
        }

        {
            std::cout << "\n[Test 2] Writing" << std::endl;
            Base32 file(testFilePath, "w", TABLE, TABLE_SIZE);
            int wrote = file.write(decodedData, decodedSize);
            std::cout << "Wrote " << wrote << " bytes" << std::endl;
        }

        std::cout << "\n=== Base32 Test Ended ===" << std::endl;
    }

    /**
     * Задание 2.2.2. RLE-сжатие.
     *
     * Создайте производный класс RleFile, который будет проводить побайтовое
     * сжатие при помощи алгоримта RLE (для простоты можно реализовать
     * неэффективный алгоритм, где последовательности без повторений отдельно
     * не кодируются).
     *
     * Переопределите методы `read` и `write`, которые будут проводить чтение из
     * файла с извлечением сжатой информации и запись в файл со сжатием
     * соответственно.
     *
     * Проверьте сжатие/извлечение на примере какого-нибудь ASCII-арта,
     * например, котенка из лабораторной №3 прошлого семестра. Посмотрите,
     * получилось ли добиться уменьшения размера хранимых данных.
     */
    
    {
        std::cout << "\n\n=== RleFile Test ===" << std::endl;
        char result[256];
        const char* testFilePath = "src/rlefiletest.txt";
        int resultLength;

        {
            std::cout << "\n[Test 1] Reading" << std::endl;
            RleFile file(testFilePath, "rb");
            resultLength = file.read(result, 256);
            if (resultLength == 0) {
                std::cerr << "Failed to read the file." << std::endl;
            } else {
                std::cout << "Read " << resultLength << " bytes:" << std::endl;
                for (int i = 0; i < resultLength; i++) {
                    std::cout << result[i];
                }
                std::cout << std::endl;
            }
        }

        {
            std::cout << "\n[Test 2] Writing" << std::endl;
            RleFile file(testFilePath, "w");
            resultLength = file.write(result, 256);
            if (resultLength == 0) {
                std::cerr << "Failed to write to the file." << std::endl;
            } else {
                std::cout << "Wrote " << resultLength << " bytes:" << std::endl;
                for (int i = 0; i < resultLength; i++) {
                    std::cout << result[i];
                }
                std::cout << std::endl;
            }
        }

        std::cout << "\n=== RleFile Test Ended ===" << std::endl;
    }

    /**
     * Задание 2.3. Конструкторы и деструкторы базового и производного классов.
     *
     * Установите отладочную печать в конструкторах и деструкторах каждого
     * класса из этого задания. Создайте локальные объекты производных классов,
     * отметьте, в каком порядке вызываются конструкторы и деструкторы при
     * инициализации и деинициализации этих классов.
     */
    
    {
        std::cout << "\n\n=== Task 2.3 ===" << std::endl;
        const char* testFilePath = "src/basefiletest.txt";
        { BaseFile file(testFilePath, "r"); }
        { Base32 file(testFilePath, "r", TABLE, TABLE_SIZE); }
        { RleFile file(testFilePath, "r"); }
    }

    /**
     * Задание 2.4. Ранее связывание.
     *
     * На основе данной заготовки напишите код, который запишет в файл строковое
     * представление целого числа. Вы должны использовать один и тот же код для
     * всех файлов, меняя только имя объекта (bf / b32f / rf), в который идет
     * запись.
     */

    {
        std::cout << "\n\n=== Task 2.4 ===" << std::endl;
        BaseFile bf("src/basefile_2-4.txt", "w");
        Base32 b32f("src/base32_2-4.txt", "w", TABLE, TABLE_SIZE);
        RleFile rf("src/rle_2-4.txt", "w");

        int n = 123456;
        char buffer1[256];
        int length1 = sprintf(buffer1, "%d", n);
        if (n < 0) { bf.write(buffer1, length1); }
        while (n > 0) {
            bf.write(buffer1, length1);
            break;
        }

        n = 123456;
        char buffer2[256];
        int length2 = sprintf(buffer2, "%d", n);
        if (n < 0) { b32f.write(buffer2, length2); }
        while (n > 0) {
            b32f.write(buffer2, length2);
            break;
        }

        n = 123456;
        char buffer3[256];
        int length3 = sprintf(buffer3, "%d", n);
        if (n < 0) { rf.write(buffer3, length3); }
        while (n > 0) {
            rf.write(buffer3, length3);
            break;
        }
    }

    /**
     * Задание 2.5. Передача объекта по ссылке / указателю.
     *
     * Прошлое задание выглядит странновато - зачем повторять код три раза?
     * Хорошо бы сделать функцию, которая примет объект файла и число, и
     * выполнит эти действия.
     *
     * Реализуйте функцию `write_int(BaseFile &file, int n)`, которая будет
     * принимать ссылку на файл и число, которое нужно будет напечатать.
     *
     * Принцип наследования предписывает, что везде, где можно использовать
     * базовый класс, можно использовать производный класс. Проверьте, можно
     * ли вызвать функцию, передав в нее объект класса Base32File и RleFile.
     *
     * Имеет ли вызов этой функции для производного класса тот же результат,
     * что и код, который вы написали выше? Почему?
     */
    
    {
        BaseFile bf("src/basefile_2-4.txt", "w");
        Base32 b32f("src/base32_2-4.txt", "w", TABLE, TABLE_SIZE);
        RleFile rf("src/rle_2-4.txt", "w");

        write_int(bf, 123456);
        write_int(b32f, 123456);
        write_int(rf, 123456);

        std::cout << sizeof(bf) << " " << sizeof(b32f) << " " << sizeof(rf) << std::endl;
    }

    /*
    No, it doesn't.
    This happens because "write" in BaseFile is not virtual.
    It leads to early binding.
    Because of that, compiler chooses which of the classes' function to use
    not during the runtime, but during compile-time, and since we put ref
    to BaseFile as the first argument to write_int, it leads to the compiler
    to choose BaseFile's write() function, not the class which is actually
    passed.
    To fix that, we must initialize write() function as virtual and override it further.
    */

    /**
     * Задание 2.6. Виртуальные функции, позднее связывание.
     *
     * Объявите функции read и write в базовом классе *виртуальными*. Что это
     * означает? Как изменился размер объектов классов BaseFile, Base32File и
     * RleFile? Почему?
     *
     * Как изменилось поведение при вызове функции `write_int` для производных
     * классов? Почему?
     */
    
    /*
    It means it can be overriden and the choice will be made during run-time, not compile-time.
    They got 8 bytes bigger. (16/32/16 ⇒ 24/40/24)
    Because now we have a vptr in vtable for virtual functions.

    Now they all work as they are meant to.
    Because now the program chooses which function to use during the run-time and sees which
    type of object we actually passed through (thus, it picks its function, not BaseFile's anytime)
    */

    /**
     * Задание 2.7. Виртуальный деструктор.
     *
     * В следующем блоке кода добавьте удаление динамической памяти.
     *
     * Какой деструктор при этом вызывается? Почему? К каким проблемам это может
     * привести?
     *
     * Исправьте эту ситуацию.
     */

    {
        BaseFile *files[] = { 
            new BaseFile("src/basefile_2-4.txt", "w"), 
            new RleFile("src/rle_2-4.txt", "w"), 
            new Base32("src/base32_2-4.txt", "w", TABLE, TABLE_SIZE), 
        };

        for (int i = 0; i < 3; ++i) {
            files[i]->write("Hello!", 6);
            delete files[i];
        }
    }

    /*
    Basically, only the destructor of parent-class is called.
    Because we initialized the array of BaseFile, compiler uses its destructor only by default.
    This can lead to... errors :)
    To correct it, we must declare BaseFile's destructor as virtual.
    */

    /**
     * Задание 2.8. Массив объектов производных классов.
     *
     * Раскомментируйте следующий блок и объясните, почему:
     * а) не возникает ошибок при компиляции;
     * б) возникают ошибки при выполнении.
     *
     * Этот пример показывает очень плохую практику, которая приводит к ошибкам;
     * для создания массива объектов производного класса и используйте массив
     * указателей на базовый класс, как это было сделано выше. Реализуйте ту же
     * логику, используя массив указателей на объекты базового класса.
     */

    {
        BaseFile *base_files = new BaseFile[1] { BaseFile("src/basefile_2-4.txt", "w") };
        BaseFile *b32_files[1] = {new Base32("src/base32_2-4.txt", "w", TABLE, TABLE_SIZE) };
        for (int i = 0; i < 1; ++i) {
            base_files[i].write("Hello!", 6);
            b32_files[i] -> write("Hello!", 6);
            delete b32_files[i];
        }
        delete [] base_files;
    }

    /*
    Because computer treats the second array as an array of BaseFile, and its size is
    different from Base32's size, so it moves wrong bytes forward along the array; memory problems.
    */

    /**
     * Задание 3. Чисто виртуальные функции. Интерфейсы. Композиция классов.
     *
     * Наследование позволяет довольно просто переиспользовать данные и логику
     * других классов, однако зачастую этот механизм недостаточно гибкий для
     * полноценного переиспользования.
     *
     * Например, сможем ли мы в получившейся иерархии классов реализовать
     * одновременно и кодирование в base32, и сжатие при записи данных в файл?
     * Или сможем ли мы вместо записи в файл на диске делать запись в строковый
     * буфер в памяти?
     *
     * При дальнейшем рассмотрении окажется, что при помощи наследования мы
     * крепко *связали* логику преобразования данных с записью в конкретный
     * файл. Далее мы рассмотрим один из способов разделения такой логики.
     */

    /**
     * Задание 3.1. Абстрактный базовый класс, чисто виртуальные функции.
     *
     * Первая проблема в нашей реализации - все наследники BaseFile будут всегда
     * обязаны непосредственно писать в файл на диске. Чтобы избавиться от этой
     * необходимости, стоит сделать базовый класс *абстрактным* в том смысле,
     * что у него не будет полей связанных с конкретным способом писать в файл.
     *
     * Создайте класс `IFile`, в котором не будет полей, но будут методы
     * `can_read`, `can_write`, `read` и `write` с такими же сигнатурами, как и
     * классе `BaseFile`. Что именно будут делать эти методы? Класс `IFile` не
     * может знать, поскольку логику этих методов будут определять наследники.
     * В этом классе эти методы не имеют реализации, и они должны быть объявлены
     * *чисто виртуальными*.
     *
     * Какие ограничения накладывает на класс наличие чисто виртуального метода?
     *
     * Получается, что в классе `IFile` есть только чисто виртуальные методы, и
     * единственная цель такого класса - определять, что должны уметь делать его
     * наследники. Совокупность действий, которые можно сделать с объектом,
     * называется его *интерфейсом*, и такие классы тоже часто называются
     * интерфейсами, отсюда берется приставка "I" в имени класса.
     *
     * Унаследуйте класс `BaseFile` от класса `IFile` и измените функцию
     * `write_int`, чтобы она работала с произвольным наследником `IFile`.
     *
     * Убедитесь, что в программе выше ничего не сломалось.
     */

    /*
    Answer: we cannot create objects from the Abstract class; we can only use it
    for creating derived classes.
    */

    /**
     * Задание 3.2. Композиция вместо наследования.
     *
     * Реализуйте классы `Base32File2` и `RleFile2`, которые будут унаследованы
     * от класса `IFile` и в конструкторе будут получать другой объект `IFile`,
     * чьи функции они будут использовать вместо функций базового класса.
     *
     * Объекты получают объект `IFile` в виде указателя на динамически
     * выделенную память, и они ответственны за ее очищение.
     *
     * Использование объектом другого объекта в качестве поля называется
     * *композицией*.
     *
     * Проверьте, что используемые ниже объекты работают так же, как объекты
     * классов `Base32File` и `RleFile`.
     */

    {
        {
            BaseFile* b32fFile = new BaseFile("src/base32_2-4.txt", "w");
            Base32File2 b32f(b32fFile, TABLE, TABLE_SIZE);
            Base32* rfFile = new Base32("src/rle_2-4.txt", "w", TABLE, TABLE_SIZE);
            RleFile2 rf(rfFile);
            write_int(b32f, 123456);
            write_int(rf, 123456);
            delete b32fFile;
            delete rfFile;
        }
        
        int BUFFER_SIZE = 256;
		char buffer[BUFFER_SIZE];
		for (int i = 0; i < BUFFER_SIZE; ++i)
			buffer[i] = 0;

		{
            BaseFile file_read1("src/base32_2-4.txt", "r");
		    BaseFile file_read2("src/rle_2-4.txt", "r");

            file_read1.read(buffer, BUFFER_SIZE);
            std::cout << "Writing 123456 via Base32File2 -> BaseFile: " << buffer << std::endl;

            for (int i = 0; i < BUFFER_SIZE; ++i)
                buffer[i] = 0;

            file_read2.read(buffer, BUFFER_SIZE);
            std::cout << "Writing 123456 via RleFile2 -> Base32File: " << buffer << std::endl;
        }

		for (int i = 0; i < BUFFER_SIZE; ++i)
			buffer[i] = 0;

        {
            BaseFile* b32fFile = new BaseFile("src/base32_2-4.txt", "r");
            Base32File2 b32f_read(b32fFile, TABLE, TABLE_SIZE);
            Base32* rfFile = new Base32("src/rle_2-4.txt", "r", TABLE, TABLE_SIZE);
            RleFile2 rf_read(rfFile);

            b32f_read.read(buffer, BUFFER_SIZE);
            std::cout << "Read number '123456' from Base32File2 -> BaseFile: " << buffer << std::endl;

            for (int i = 0; i < BUFFER_SIZE; ++i)
                buffer[i] = 0;

            rf_read.read(buffer, BUFFER_SIZE);
            std::cout << "Read number '123456' from RleFile2 -> Base32File: " << buffer << std::endl;

            delete b32fFile;
            delete rfFile;
        }
    }

    /**
     * Задание 3.3. Больше композиции!
     *
     * Не реализовывая больше никаких классов, соорудите объект-наследник IFile,
     * который будет при вызове метода `write` два раза кодировать в base32,
     * после чего применять сжатие RLE и только после этого писать в файл.
     */

    {
        IFile* basefile = new BaseFile("src/rle_3-3.txt", "w");
        IFile* rlefile = new RleFile2(basefile);
        IFile* base32file = new Base32File2(rlefile, TABLE, TABLE_SIZE);
        IFile* encodedTwice = new Base32File2(base32file, TABLE, TABLE_SIZE);

        write_int(*encodedTwice, 123456);

        delete encodedTwice;
        delete base32file;
        delete rlefile;
        delete basefile;
    }

    return 0;
}
