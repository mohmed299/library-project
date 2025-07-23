#include <stdio.h>
#include <stdlib.h>
#include "book.h"

// عرض جميع الكتب المتاحة (التي لم يتم استعارتها)
void viewAvailableBooks() {
    Book b;
    FILE *fp = fopen("books.txt", "r");

    if (!fp) {
        printf("لا يوجد كتب حالياً.\n");
        return;
    }

    printf("\nقائمة الكتب المتاحة:\n");
    while (fread(&b, sizeof(Book), 1, fp)) {
        if (!b.isBorrowed) {
            printf("ID: %d | %s by %s (%d)\n", b.id, b.title, b.author, b.year);
        }
    }

    fclose(fp);
}

// استعارة كتاب معين بواسطة رقم التعريف
void borrowBook() {
    int id, found = 0;
    Book b;

    FILE *fp = fopen("books.txt", "r");
    FILE *temp = fopen("temp.txt", "w");

    if (!fp || !temp) {
        printf("حدث خطأ أثناء فتح الملفات.\n");
        return;
    }

    printf("أدخل رقم ID الخاص بالكتاب الذي تريد استعارته: ");
    scanf("%d", &id);

    while (fread(&b, sizeof(Book), 1, fp)) {
        if (b.id == id && !b.isBorrowed) {
            b.isBorrowed = 1;
            found = 1;
        }
        fwrite(&b, sizeof(Book), 1, temp);
    }

    fclose(fp);
    fclose(temp);
    remove("books.txt");
    rename("temp.txt", "books.txt");

    if (found)
        printf("تم استعارة الكتاب بنجاح.\n");
    else
        printf("الكتاب غير موجود أو مستعار بالفعل.\n");
}

// إرجاع كتاب تم استعارته سابقًا
void returnBook() {
    int id, found = 0;
    Book b;

    FILE *fp = fopen("books.txt", "r");
    FILE *temp = fopen("temp.txt", "w");

    if (!fp || !temp) {
        printf("حدث خطأ أثناء فتح الملفات.\n");
        return;
    }

    printf("أدخل رقم ID الخاص بالكتاب الذي تريد إرجاعه: ");
    scanf("%d", &id);

    while (fread(&b, sizeof(Book), 1, fp)) {
        if (b.id == id && b.isBorrowed) {
            b.isBorrowed = 0;
            found = 1;
        }
        fwrite(&b, sizeof(Book), 1, temp);
    }

    fclose(fp);
    fclose(temp);
    remove("books.txt");
    rename("temp.txt", "books.txt");

    if (found)
        printf("تم إرجاع الكتاب بنجاح.\n");
    else
        printf("الكتاب غير موجود أو لم يتم استعارته.\n");
}
