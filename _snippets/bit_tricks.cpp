======================= PART I ==========================
#ifndef _AVR035_H_
#define _AVR035_H_

// from AVR035: Efficient C Coding for AVR

#define SETBIT(ADDRESS,BIT) (ADDRESS |= (1<<BIT))
#define CLEARBIT(ADDRESS,BIT) (ADDRESS &= ~(1<<BIT))
#define FLIPBIT(ADDRESS,BIT) (ADDRESS ^= (1<<BIT))
#define CHECKBIT(ADDRESS,BIT) (ADDRESS & (1<<BIT))

#define SETBITMASK(x,y) (x |= (y))
#define CLEARBITMASK(x,y) (x &= (~y))
#define FLIPBITMASK(x,y) (x ^= (y))
#define CHECKBITMASK(x,y) (x & (y))


Чтобы установить бит в регистре в значение 1, не изменяя значения других битов, используется команда вида:

регистр |= (1 << номер_бита);

А чтобы установить бит в регистре в значение 0, так же не изменяя значения других битов, используется команда вида:

регистр &= ~ (1 << номер_бита);

//reg : имя переменной, регистра
//bit : позиция бита
//val : 0 или 1
#define Bit(bit)  (1<<(bit))

#define ClearBit(reg, bit)       reg &= (~(1<<(bit)))
//пример: ClearBit(PORTB, 1); //сбросить 1-й бит PORTB

#define SetBit(reg, bit)          reg |= (1<<(bit))
//пример: SetBit(PORTB, 3); //установить 3-й бит PORTB

#define SetBitVal(reg, bit, val) do{if ((val&1)==0) reg &= (~(1<<(bit)));\
                                  else reg |= (1<<(bit));}while(0)
//пример: SetBitVal(PORTB, 3, 1); //установить 3-й бит PORTB
//	  SetBitVal(PORTB, 2, 0); //сбросить 2-й бит PORTB

#define BitIsClear(reg, bit)    ((reg & (1<<(bit))) == 0)
//пример: if (BitIsClear(PORTB,1)) {...} //если бит очищен

#define BitIsSet(reg, bit)       ((reg & (1<<(bit))) != 0)
//пример: if(BitIsSet(PORTB,2)) {...} //если бит установлен

#define InvBit(reg, bit)	  reg ^= (1<<(bit))
//пример: InvBit(PORTB, 1); //инвертировать 1-й бит PORTB

#endif//BITS_MACROS_

#endif 

======================= PART II ==========================
Как работать с битами. 

При программировании микроконтроллеров постоянно приходится работать с битами. Устанавливать их, сбрасывать,  проверять их наличие в том или ином регистре. В AVR ассемблере для этих целей существует целый ряд команд. Во-первых, это группа команд операций с битами – они предназначены для установки или сброса битов в различных регистрах микроконтроллера, а во-вторых, группа команд передачи управления – они предназначены для организации ветвлений программ. В языке Си естественно нет подобных команд, поэтому у начинающих программистов часто возникает вопрос, а как в Си работать с битами. Эту тему мы сейчас и будем разбирать.

   В Си существуют 6 операторов для манипулирования битами. Их можно применять к любым целочисленным знаковым или беззнаковым типам переменных.

"<<  - сдвиг влево"
">>  - сдвиг вправо"
"~   -  поразрядная инверсия"
"|    - поразрядное ИЛИ"
"^   -  поразрядное исключающее ИЛИ"
_______________ сдвиг влево "<<" _______________
   Сдвигает число на n разрядов влево. Старшие n разрядов при этом исчезают, а младшие n  разрядов заполняются нулями.
        
        unsigned char tmp = 3;  //0b00000011    
        tmp = tmp << 1;   
        //теперь в переменной tmp число 6 или 0b00000110
        
        tmp = tmp << 3;
        //теперь в переменной tmp число 48  или 0b00110000

   Выражения, в которых над переменной производится какая-либо операция, а потом результат операции присваивается этой же переменной, можно записывать короче, используя составные операторы. 

        tmp = 7;  //0b00000111    
        tmp <<= 2; //сокращенный вариант записи
        //теперь в переменной tmp число 28 или 0b00011100

Операция сдвига влево на n разрядов эквивалентна умножению переменной на 2n.

_______________ сдвиг вправо >> _______________
   Сдвигает число на n разрядов вправо. Младшие n разрядов при этом теряются. Заполнение старших n  разрядов зависит от типа переменной и ее значения. Старшие n разрядов заполняются нулями в двух случаях – если переменная беззнакового типа или если переменная знаковая и ее текущее значение положительное. Когда переменная знаковая и ее значение отрицательное – старшие разряды заполняются единицами.    

Пример для беззнаковой переменной 

        unsigned char tmp = 255;  //0b11111111
        tmp = tmp >> 1;
        //теперь в переменной tmp число 127 или 0b01111111
        
        tmp >>=  3;  //сокращенный вариант записи
        //теперь в переменной tmp число 15 или 0b00001111

Пример для переменной знакового типа 
        
        int tmp = 3400; //0b0000110101001000
        tmp >>= 2;
        //теперь в переменной число 850 или 0b0000001101010010

        tmp = -1200; //0b1111101101010000
        tmp >>= 2;
        //теперь в tmp число -300 или 0b1111111011010100
        //видите - два старших разряда заполнились единицами

   Операция сдвига вправо на n разрядов эквивалентна делению на 2n. При этом есть некоторые нюансы. Если потерянные младшие разряды содержали единицы, то результат подобного “деления” получается грубоватым.

Например    9/4 = 2,5         а 9>>2      (1001>>2)    равно 2
                  11/4 = 2,75     а 11>>2      (1011>>2)    равно 2    
                  28/4 = 7          а 28>>2    (11100>>2)    равно 7     
   
Во втором случае ошибка больше, потому что оба младших разряда единицы. В третьем случае ошибки нет, потому что потерянные разряды нулевые.

_______________поразрядная инверсия ~ _______________
   Поразрядно инвертирует число. Разряды, в которых были нули – заполняются единицами. Разряды, в которых были единицы – заполняются нулями. Оператор поразрядной инверсии являтся унарным оператором, то есть используется с одним операндом.

        unsigned char tmp =  94;     //0b01011110
        tmp = ~tmp;
        //теперь в переменной tmp число 161 или 0b10100001
        
        tmp = ~tmp;
        //теперь в tmp снова число 94 или 0b01011110

_______________ поразрядное ИЛИ | ______________
 
 
Оператор | осуществляет операцию логического ИЛИ между соответствующими битами  двух операндов. Результатом операции логического ИЛИ между двумя битами будет 0 только в случае, если оба бита равны 0. Во всех остальных случаях результат будет 1. Это проиллюстрировано в табице истинности.
 
 
Оператор | обычно используют для установки заданных битов переменной в единицу. 
        
    tmp = 155
    tmp = tmp | 4; //устанавливаем в единицу второй бит переменной tmp

    155     0b10011011    
|
        4     0b00000100    
    159     0b10011111
   Использовать десятичные числа для установки битов довольно неудобно. Гораздо удобнее это делать с помощью операции сдвига влево <<.

    tmp = tmp | (1<<4); //устанавливаем в единицу четвертый бит переменной tmp
   Читаем справа налево – сдвинуть единицу на четыре разряда влево, выполнить операцию ИЛИ между полученным числом и значением переменной tmp, результат присвоить переменной tmp.

Установить несколько битов в единицу можно так

    tmp = tmp | (1<<7)|(1<<5)|(1<<0);
   //устанавливаем в единицу седьмой, пятый и нулевой биты переменной tmp
    
С помощью составного оператора присваивания  |= можно сделать запись компактней.

    tmp |= (1<<4); 
    tmp |= (1<<7)|(1<<5)|(1<<0);
_______________ побитовое И & _______________


 
   Оператор & осуществляет операцию логического И между соответствующими битами двух операндов. Результатом операции логического И между двумя битами будет 1 только в том случае, если оба бита равны 1. Во всех других случаях результат будет 0. Это проиллюстрировано в таблице истинности.
 
 
Оператор & обычно применяют, чтобы обнулить один или несколько битов. 
    
    tmp = 155;        
    tmp = tmp & 247; //обнуляем третий бит переменной tmp


    155        0b10011011    
&
    247        0b11110111    
    147        0b10010011

Видите, третий бит стал равен 0, а остальные биты не изменились.

Обнулять биты, используя десятичные цифры, неудобно. Но можно облегчить себе жизнь, воспользовавшись операторами << и ~

    tmp = 155;
    tmp = tmp & (~(1<<3)); //обнуляем третий бит 

1<<3                          0b00001000 
~(1<<3)                     0b11110111
tmp & (~(1<<3))        0b10011011 & 0b11110111
результат                    0b10010011
   Читаем справа налево – сдвинуть единицу на три разряда влево, выполнить инверсию полученного числа, выполнить операцию & между значением переменной tmp и проинвертированным числом, результат присвоить переменной tmp.

Обнулить несколько битов можно так
    tmp = tmp & (~((1<<3)|(1<<5)|(1<<6))); //обнуляем третий, пятый и шестой биты

   Здесь сначала выполняются операции сдвига, потом операции поразрядного ИЛИ, затем инверсия, поразрядное И, присвоение результата переменной tmp.

Используя составной оператор присваивания &= ,можно записать выражение более компактно

    tmp &= (~((1<<3)|(1<<5)|(1<<6)));

   Как проверить установлен ли бит в переменной? Нужно обнулить все биты, кроме проверочного, а потом сравнить полученное значение с нулем 
    
   if ((tmp & (1<<2)) != 0 ){
      // блок будет выполняться, только если установлен
      // второй бит переменной tmp
   }

    if ((tmp & (1<<2)) == 0 ){
      // блок будет выполняться, только если не установлен
      // второй бит переменной tmp
    }
    _______________побитовое исключающее ИЛИ ^ _______________  


   Оператор ^ осуществляет операцию логического исключающего ИЛИ между соответствующими битами двух операндов. Результатом операции логического исключающего ИЛИ будет 0 в случае равенства битов. Во всех остальных случаях результат будет 1. Это проиллюстрировано в табице истинности. 
  
   Оператор ^ применяется не так часто как остальные битовые операторы, но и для него находится работенка. Например, с помощью него можно инвертировать один или несколько битов переменной.

    tmp = 155;
    tmp = tmp ^ 8; // инвертируем четвертый бит переменой tmp
    
    155         0b10011011    
^
    8             0b00001000    
    147         0b10010011

Четвертый бит изменил свое значение на противоположное, а остальные биты остались без изменений. 

    tmp = tmp ^ 8; // опять инвертируем четвертый бит переменой tmp

    147         0b10010011    
^
    8             0b00001000    
    155         0b10011011

Видите, четвертый бит снова изменил свое значение на противоположное.  

Так записывать выражение намного удобнее

    tmp = tmp ^ (1<<3); // инвертируем третий бит переменой tmp
    
А так и удобно и компактно

    tmp ^= (1<<4);  //инвертируем четверый бит

Можно инвертировать несколько битов одновременно

    tmp ^= ((1<<4)|(1<<2)|(1<<1)); //инвертируем 4,2 и 1 биты   
    У поразрядного исключающего ИЛИ есть еще одно интересное свойство. Его можно использовать, для того чтобы поменять значения двух переменных местами. Обычно для этого требуется третья переменная.

tmp = var1;
var1 = var2;
var2 = tmp;

Но используя оператор ^  переставить значения можно так:

var1 ^= var 2;
var 2 ^= var 1;
var 1 ^= var 2;

Чистая магия, хотя, честно говоря,  я ни разу не пользовался таким приемом.
________________Директива #define__________________

   Теперь мы знаем, как устанавливать, обнулять и инвертировать биты, знаем, как проверять установлен ли бит или нет. Рассмотренные выше выражения довольно громоздки, но с помощью директивы препроцессора #define, им можно придать более приятный вид.
   Директива #define используется для присваивания символических имен константам и для макроопределений. Использование символических имен делают программу более модифицируемой и переносимой.
    Например, вы используете в тексте программы константу, и вдруг вам понадобилось изменить ее значение. Если она встречается всего в трех местах, то исправить ее можно и в ручную, а что делать, если она встречается в пятидесяти строчках? Мало того, что исправление займет много времени, так еще и ошибиться в этом случае проще простого. Здесь то, как раз и выручает директива#define. В начале программы задается символическое имя константы, которое  используется по ходу программы. Если нам нужно изменить это значение, это делается всего лишь в одном месте. А перед компиляцией препроцессор сам подставит во все выражения вместо имени константы ее значение.
    Программирование микроконтроллера неразрывно связано  с его аппаратной частью и чаще всего с внешней обвязкой. Взять хотя бы кнопки - опрашивая их в своей программе, мы обращаемся к реальным выводам микроконтроллера. А если нам вдруг понадобилось использовать программу опроса кнопок в другой схеме, где кнопки подключены к другим выводам? Придется исправлять программу. Опять таки, задав с помощью директивы #define символическое имя для соответствующих выводов, модифицировать программу будет проще простого

Пример:

#include "iom8535.h"

//порт, к которому подключены кнопки
#define PORT_BUTTON     PORTA
#define PIN_BUTTON        PINA
#define DDRX_BUTTON     DDRA

//выводы, к которым подключены кнопки
#define DOWN        3
#define CANCEL      4
#define UP              5
#define ENTER         6

int main()
{
    //конфигурируем порт на вход, 
    //и включаем подтягивающие резисторы
    DDRX_BUTTON = 0;    
    PORT_BUTTON = 0xff;
    
…..
}


При задании символического имени можно использовать и выражения 

#define MASK_BUTTONS       ((1<<DOWN)|(1<<CANCEL)|(1<<UP)|(1<<ENTER))

пример использования:
tmp = PORTB & MASK_BUTTONS;

Используя #define не жалейте скобок чтобы четко задать последовательность вычисления выражений!

Некоторые выражения можно замаскировать под «функции». 

#define ADC_OFF()             ADCSRA = 0

пример использования:
ADC_OFF();

Можно использовать многострочные определения, используя в конце каждой строки символ \ 

#define INIT_Timer()        TIMSK = (1<<OCIE0);\
                                       TCCR0 = (1<<WGM01)|(0<<WGM00)|(1<<CS02);\
                                       TCNT0 = 0;\
                                       OCR0 = 0x7d

пример использования:
INIT_Timer();

 
Ну и самое мощное применение директивы #define – это задание макроопределений (или просто макросов). Вот как с помощью#define можно задать макросы для рассмотренных ранее операций с битами

#define   SetBit(reg, bit)          reg |= (1<<bit)            
#define   ClearBit(reg, bit)       reg &= (~(1<<bit))
#define   InvBit(reg, bit)          reg ^= (1<<bit)
#define   BitIsSet(reg, bit)       ((reg & (1<<bit)) != 0)
#define   BitIsClear(reg, bit)    ((reg & (1<<bit)) == 0)

пример использования:
…
SetBit(PORTB, 0);    //установить нулевой бит порта B    
InvBit(tmp,6);         //инвертировать шестой бит переменной tmp

…
if  (BitIsClear(PIND, 0)) {   //если очищен нулевой бит в регистре PIND                                     
…..                                     //выполнить блок
}
   Перед компиляцией препроцессор заменит эти строчки объявленными  ранее выражениями, подставив в них соответствующие аргументы.
   Макросы очень мощное средство, но использовать их нужно осторожно. Вот самые распространенные грабли, о которых написано во всех учебниках по программированию.
Определим макрос, вычисляющий квадрат числа:

#define SQUARE(x)    x*x

выражение    
tmp =  SQUARE(my_var);
даст корректный результат.

А что будет если в качестве аргумента макроопределения использовать выражение my_var+1

tmp =  SQUARE(my_var +1);

Препроцессор заменит эту строчку на 

tmp = my_var + 1 * my_var +1;

а это вовсе не тот результат, который мы ожидаем.

Чтобы избежать таких ошибок не скупитесь на скобки при объявлении макросов!

Если объявить макрос так

#define SQUARE(x)    ((x)*(x))

выражение 
tmp =  SQUARE(my_var +1);
даст корректный результат, потому что препроцессор заменит эту строчку на
tmp = ((my_var + 1) * (my_var +1));

======================= PART III =========================


Programming 101 - By Eric Weddington

To really understand what's going, it's best to learn C languages bit operators and about truth tables.

    | bit OR
    & bit AND
    ~ bit NOT
    ^ bit EXLUSIVE OR (XOR)
    << bit LEFT SHIFT
    >> bit RIGHT SHIFT



These operators work on bits and not logical values. Take two 8 bit bytes, combine with any of these operators, and you will get another 8 bit byte according to the operator's function. These operators work on the individual bits inside the byte.

A truth table helps to explain each operation. In a truth table, a 1 bit stands for true, and a 0 stands for false.

The OR operation truth table:

    0 OR 0 = 0
    0 OR 1 = 1
    1 OR 0 = 1
    1 OR 1 = 1



The AND operation truth table:

    0 AND 0 = 0
    0 AND 1 = 0
    1 AND 0 = 0
    1 AND 1 = 1



The XOR operation truth table:

    0 XOR 0 = 0
    0 XOR 1 = 1
    1 XOR 0 = 1
    1 XOR 1 = 0



The NOT operator inverts the sense of the bit, so a 1 becomes a 0, and a 0 becomes a 1.

So let's say I have a byte foo that is initialized to 0:
Code:
unsigned char foo = 0;


To set bit 0 in foo and then store the result back into foo:
Code:
foo = foo | 0x01;


The OR operation is used between the variable that we want to change and a constant which is called a BIT MASK or simply the MASK. The mask is used to identify the bit that we want changed.

Remember that we write the constants in hexadecimal because it's' shorter than writing it in binary. It is assumed that the reader knows how to convert back and forth between hex and binary. Wink

Usually, though the statement is made shorter in real programming practice to take advantage of C compound assignment:

Code:
foo |= 0x01;


This is equivalent to the statement above.

To clear bit 0 in foo requires 2 bit operators:

Code:
foo = foo & ~0x01;


This uses the AND operator and the NOT operator. Why do we use the NOT operator? Most programmers find it easier to specify a mask wherein the bit that they are interested in changing, is set. However, this kind of mask can only be used in setting a bit (using the OR operator). To clear a bit, the mask must be inverted and then ANDed with the variable in question. It is up to the reader to do the math to show why this works in clearing the desired bit.

Again, the statement is made shorter with a compound assignment:

Code:
foo &= ~0x01;


To see if a bit is set or clear just requires the AND operator, but with no assignment. To see if bit 7 is set in the variable foo:

Code:
if(foo & 0x80)
{
}


The condition will be zero if the bit is clear, and the condition will be non-zero if the bit is set. NOTE! The condition will be NON-ZERO when the bit is set. But the condition will not NECESSARILY BE ONE. It is left to the reader to calculate the value of the condition to understand why this is the case.


There is another useful tool that is not often seen, and that is when you want to flip a bit, but you don't know and you don't care what state the bit is currently in. Then you would use the XOR operator:

Code:
foo = foo ^ 0x01;


Or the shorter statement:

Code:
foo ^= 0x01;


A lot of times the bit mask is built up dynamically in other statements and stored in a variable to be used in the assignment statement:

Code:
foo |= bar;


Sometimes, a programmer wants to specify the bit NUMBER that they want to change and not the bit MASK. The bit number always starts at 0 and increases by 1 for each bit. An 8 bit byte has bit numbers 0-7 inclusive. The way to build a bit mask with only a bit number is to LEFT SHIFT a bit by the bit number. To build a bit mask that has bit number 2 set:

Code:
(0x01 << 2)


To build a bit mask that has bit number 7 set:

Code:
(0x01 << 7)


To build a bit mask that has bit number 0 set:

Code:
(0x01 << 0)


Which ends up shifting the constant 0 bytes to the left, leaving it at 0x01.



MACROS

Because there are a number of programmers who do not seem to have a familiarity with bit flipping (because they weren't taught it at school, or they don't need to know it because of working on PCs), most programmers usually write macros for all of these operations. Also, it provides a fast way of understanding what is happening when reading the code, or it provides additional functionality.

Below is a set of macros that works with ANSI C to do bit operations:

Code:
#define bit_get(p,m) ((p) & (m))
#define bit_set(p,m) ((p) |= (m))
#define bit_clear(p,m) ((p) &= ~(m))
#define bit_flip(p,m) ((p) ^= (m))
#define bit_write(c,p,m) (c ? bit_set(p,m) : bit_clear(p,m))
#define BIT(x) (0x01 << (x))
#define LONGBIT(x) ((unsigned long)0x00000001 << (x))



To set a bit:
Code:
bit_set(foo, 0x01);


To set bit number 5:
Code:
bit_set(foo, BIT(5));


To clear bit number 6 with a bit mask:
Code:
bit_clear(foo, 0x40);


To flip bit number 0:
Code:
bit_flip(foo, BIT(0));


To check bit number 3:
Code:
if(bit_get(foo, BIT(3)))
{
}


To set or clear a bit based on bit number 4:
Code:
if(bit_get(foo, BIT(4)))
{
    bit_set(bar, BIT(0));
}
else
{
    bit_clear(bar, BIT(0));
}



To do it with a macro:
Code:
bit_write(bit_get(foo, BIT(4)), bar, BIT(0));


If you are using an unsigned long (32 bit) variable foo, and have to change a bit, use the macro LONGBIT which creates un unsigned long mask. Otherwise, using the BIT() macro, the compiler will truncate the value to 16-bits.[/list]


