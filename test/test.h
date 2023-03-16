#define TEST(cond,testName) printf("%s:%s\n", (cond) ? "OK" : "FAIL", testName);
#define TESTSTREQ(a,b,testName)  printf("%s: %s %s==%s\n", (strcmp(a,b)==0) ? "OK" : "FAIL", testName, a, b);
#define TESTLONGEQ(a,b,testName) printf("%s: %s %ld==%ld\n", ((a)==(b)) ? "OK" : "FAIL", testName, a, b);
