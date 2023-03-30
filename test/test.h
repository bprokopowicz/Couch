#define TEST(cond,testName) printf("%s() %s:%s\n", __func__, (cond) ? "OK" : "FAIL", testName);
#define TESTSTREQ(a,b,testName)  printf("%s() %s: %s %s==%s\n", __func__, (strcmp(a,b)==0) ? "OK" : "FAIL", testName, a, b);
#define TESTLONGEQ(a,b,testName) printf("%s() %s: %s %ld==%ld\n", __func__, ((a)==(b)) ? "OK" : "FAIL", testName, a, b);
