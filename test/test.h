#define TEST(cond,testName) printf("%s:%s\n",  testName, (cond) ? "OK" : "FAIL");
#define TESTSTREQ(a,b,testName) printf("%s: %s==%s %s\n", testName, a, b, (strcmp(a,b)==0) ? "OK" : "FAIL");
#define TESTLONGEQ(a,b,testName) printf("%s: %ld==%ld %s\n", testName, a, b, (a)==(b) ? "OK" : "FAIL");
