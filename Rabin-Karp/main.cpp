#include <stdio.h>

char* RabinKarp(const char* str, const char* substr);

int main() {
    const char string[] = "I LOVE MATH! AAAAAkfjkdhsaksfgjkhofdj'piohjsotjkhbojfgiknjhgbml;bjfgmkn,xgjmnl;K;v'fLDhkjnhkngb l;,kb,;'fdklbjnkbnlfdkbldnbnkl;bnkl;'fgkl;kfgm'aifgjihrgjdhnvmnvmkxzcngbuhiufagjkrewgjkfdbn,mvcnbjkfdhghsdfhlkjfdkgbjL:XKFOhdjkfjdng,kdxml;GFKodzjhklijndfkhzjmkjhmknjkghjikfhjkgfnmkgfhxjmDDDD";
    const char substr1[] = "MATH!";
    const char substr2[] = "MATCH";
    const char substr3[] = "ufagjkrewgjkfdbn,mvcnbjkfdhghsdfhlkjfdkgbjL:XKFOhdjkfjdng,kdxml;GFKodzjhklijndfkhzjmkjhmknjkgh";
    const char substr4[] = "I DONT LIKE MATH";

    char* ans = RabinKarp(string, substr1);
    if (ans) printf("%s\n", ans);
    else printf("Not found\n");

    ans = RabinKarp(string, substr2);
    if (ans) printf("%s\n", ans);
    else printf("Not found\n");

    ans = RabinKarp(string, substr3);
    if (ans) printf("%s\n", ans);
    else printf("Not found\n");

    ans = RabinKarp(string, substr4);
    if (ans) printf("%s\n", ans);
    else printf("Not found\n");

}
