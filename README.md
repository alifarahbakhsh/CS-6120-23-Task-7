# Swapping the operands of integer addition and multiplication
The title explains everything. Here is an output snippet of applying the pass on a simple C program:
`Before swapping:
  %1 = alloca i32, align 4!
  %2 = alloca i32, align 4!
  %3 = alloca i32, align 4!
  %4 = alloca i32, align 4!
  %5 = alloca i32, align 4!
  store i32 0, ptr %1, align 4!
  store i32 8, ptr %2, align 4!
  store i32 3, ptr %3, align 4!
  %6 = load i32, ptr %2, align 4!
  %7 = load i32, ptr %3, align 4!
  %8 = add nsw i32 %6, %7!
  store i32 %8, ptr %4, align 4!
  %9 = load i32, ptr %4, align 4!
  %10 = mul nsw i32 %9, 2!
  store i32 %10, ptr %5, align 4!
  %11 = load i32, ptr %5, align 4!
  %12 = call i32 (ptr, ...) @printf(ptr noundef @.str, i32 noundef %11)!
  ret i32 0!
After swapping:
  %1 = alloca i32, align 4!
  %2 = alloca i32, align 4!
  %3 = alloca i32, align 4!
  %4 = alloca i32, align 4!
  %5 = alloca i32, align 4!
  store i32 0, ptr %1, align 4!
  store i32 8, ptr %2, align 4!
  store i32 3, ptr %3, align 4!
  %6 = load i32, ptr %2, align 4!
  %7 = load i32, ptr %3, align 4!
  %8 = add nsw i32 %7, %6!
  store i32 %8, ptr %4, align 4!
  %9 = load i32, ptr %4, align 4!
  %10 = mul nsw i32 2, %9!
  store i32 %10, ptr %5, align 4!
  %11 = load i32, ptr %5, align 4!
  %12 = call i32 (ptr, ...) @printf(ptr noundef @.str, i32 noundef %11)!
  ret i32 0!`

Here is the program itself:
`#include <stdio.h>
int main() {
   int a = 2 * 4;
   int b = 3;
   int c = a + b;
   int d = c * 2;
   printf("%i", d);
   return 0;
}`
