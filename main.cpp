#include <iostream>
#include "task1.h"
#include "task2.h"
#include "task3.h"
#include "task4.h"
#include "Task5.h"
#include "Task6.h"
#include "task7.h"
#include "Task8.h"
#include "task9.h"
#include "task10.h"
#include "task11.h"
#include "task12.h"
#include "task13.h"
#include "task14.h"
#include "task15.h"
#include "Task16.h"
#include "Task17.h"
#include "task18.h"
#include "task19.h"
#include "Task20.h"
#include "Task21.h"
#include "task22.h"
#include "task23.h"
#include "Task24.h"
#include "task25.h"

int main() {

  std::cout << "+--- --- --- --- --- --- --- --- --- --- --- ---" << std::endl;
  std::cout << "Task1 - example data" << std::endl;
  Task1 task1(true);
  task1.solve1();
  task1.solve2();
  std::cout << "Task1 - task data" << std::endl;
  Task1 task1b(false);
  task1b.solve1();
  task1b.solve2();

  std::cout << "+--- --- --- --- --- --- --- --- --- --- --- ---" << std::endl;
  std::cout << "Task2 - example data" << std::endl;
  Task2 task2(true);
  task2.solve1();
  task2.solve2();
  std::cout << "Task2 - task data" << std::endl;
  Task2 task2b(false);
  task2b.solve1();
  task2b.solve2();

  std::cout << "+--- --- --- --- --- --- --- --- --- --- --- ---" << std::endl;
  std::cout << "Task3 - example data" << std::endl;
  Task3 task3(true);
  task3.Solve1();
  task3.Solve2();
  std::cout << "Task3 - task data" << std::endl;
  Task3 task3b(false);
  task3b.Solve1();
  task3b.Solve2();

  std::cout << "+--- --- --- --- --- --- --- --- --- --- --- ---" << std::endl;
  std::cout << "Task4 - example data" << std::endl;
  Task4 task4(true);
  task4.solve1();
  task4.solve2();
  std::cout << "Task4 - task data" << std::endl;
  Task4 task4b(false);
  task4b.solve1();
  task4b.solve2();

  std::cout << "+--- --- --- --- --- --- --- --- --- --- --- ---" << std::endl;
  std::cout << "Task5 - example data" << std::endl;
  Task5 task5(true);
  task5.solve1();
  task5.solve2();
  std::cout << "Task5 - task data" << std::endl;
  Task5 task5b(false);
  task5b.solve1();
  task5b.solve2();

  std::cout << "+--- --- --- --- --- --- --- --- --- --- --- ---" << std::endl;
  std::cout << "Task6 - example data" << std::endl;
  Task6 task6(true);
  task6.solve1();
  task6.solve2();
  std::cout << "Task6 - task data" << std::endl;
  Task6 task6b(false);
  task6b.solve1();
  task6b.solve2();

  std::cout << "+--- --- --- --- --- --- --- --- --- --- --- ---" << std::endl;
  std::cout << "Task7 - example data" << std::endl;
  Task7 task7(true);
  task7.solve1();
  Task7 task7b(true, false);
  task7b.solve2();
  std::cout << "Task7 - task data" << std::endl;
  Task7 task7c(false);
  task7c.solve1();
  task7c.solve2();

  std::cout << "+--- --- --- --- --- --- --- --- --- --- --- ---" << std::endl;
  std::cout << "Task8 - example data" << std::endl;
  Task8 task8(true);
  task8.solve1();
  task8.solve2();
  std::cout << "Task8 - task data" << std::endl;
  Task8 task8b(false);
  task8b.solve1();
  task8b.solve2();

  std::cout << "+--- --- --- --- --- --- --- --- --- --- --- ---" << std::endl;
  std::cout << "Task9 - example data" << std::endl;
  task9 task9a{true};
  task9a.solve1();
  task9a.solve2();
  std::cout << "Task9 - task data" << std::endl;
  task9 task9b{false};
  task9b.solve1();
  task9b.solve2();

  std::cout << "+--- --- --- --- --- --- --- --- --- --- --- ---" << std::endl;
  std::cout << "Task10 - example data" << std::endl;
  Task10 task10{true};
  task10.solve1();
  task10.solve2();
  std::cout << "Task10 - task data" << std::endl;
  Task10 task10b{false};
  task10b.solve1();
  task10b.solve2();

  std::cout << "+--- --- --- --- --- --- --- --- --- --- --- ---" << std::endl;
  std::cout << "Task11 - example data" << std::endl;
  Task11 task11(true);
  task11.solve1();
  task11.solve2();
  std::cout << "Task11 - task data" << std::endl;
  Task11 task11b(false);
  task11b.solve1();
  task11b.solve2();

  std::cout << "+--- --- --- --- --- --- --- --- --- --- --- ---" << std::endl;
  std::cout << "Task12 - example data" << std::endl;
  Task12 task12(true);
  task12.solve1();
  task12.solve2();
  std::cout << "Task12 - test data" << std::endl;
  Task12 task12b(false);
  task12b.solve1();
  task12b.solve2();

  std::cout << "+--- --- --- --- --- --- --- --- --- --- --- ---" << std::endl;
  std::cout << "Task13 - example data" << std::endl;
  Task13 task13(true);
  task13.solve1();
  task13.solve2();
  std::cout << "Task13 - task data" << std::endl;
  Task13 task13b(false);
  task13b.solve1();
  task13b.solve2();

  std::cout << "+--- --- --- --- --- --- --- --- --- --- --- ---" << std::endl;
  std::cout << "Task14 - example data" << std::endl;
  Task14 task14(true);
  task14.solve1();
  Task14 task14b(true, true);
  task14b.solve2();
  std::cout << "Task14 - task data" << std::endl;
  Task14 task14c(false);
  task14c.solve1();
  task14c.solve2();

  std::cout << "+--- --- --- --- --- --- --- --- --- --- --- ---" << std::endl;
  std::cout << "Task15 - example data" << std::endl;
  Task15 task15(true);
  task15.solve1();
  std::cout << "!!! this is slow under debug mode, better run in release." << std::endl;
  task15.solve2();
  std::cout << "Task15 - task data" << std::endl;
  Task15 task15b(false);
  task15b.solve1();
  task15b.solve2();

  std::cout << "+--- --- --- --- --- --- --- --- --- --- --- ---" << std::endl;
  std::cout << "Task16 - example data" << std::endl;
  Task16 task16(true);
  task16.solve1();
  task16.solve2();
  std::cout << "Task16 - task data" << std::endl;
  Task16 task16b(false);
  task16b.solve1();
  task16b.solve2();

  std::cout << "+--- --- --- --- --- --- --- --- --- --- --- ---" << std::endl;
  std::cout << "Task17 - example data" << std::endl;
  Task17 task17(true);
  task17.solve1();
  task17.solve2();
  std::cout << "Task17 - task data" << std::endl;
  Task17 task17b(false);
  task17b.solve1();
  task17b.solve2();

  std::cout << "+--- --- --- --- --- --- --- --- --- --- --- ---" << std::endl;
  std::cout << "Task18 - example data" << std::endl;
  Task18 task18(true);
  task18.solve1();
  task18.solve2();
  std::cout << "Task18 - task data" << std::endl;
  Task18 task18b(false);
  task18b.solve1();
  task18b.solve2();

  std::cout << "+--- --- --- --- --- --- --- --- --- --- --- ---" << std::endl;
  std::cout << "Task19 - example data" << std::endl;
  Task19 task19(true, false);
  task19.solve1();
  Task19 task19b(true, true);
  task19b.solve2();
  std::cout << "Task19 - example data" << std::endl;
  Task19 task19c(false, false);
  task19c.solve1();
  Task19 task19d(false, false);
  task19d.solve2();

  std::cout << "+--- --- --- --- --- --- --- --- --- --- --- ---" << std::endl;
  std::cout << "Task20 - example data" << std::endl;
  Task20 task20(true);
  task20.solve1();
  task20.solve2();
  std::cout << "Task20 - example data" << std::endl;
  Task20 task20b(false);
  task20b.solve1();
  task20b.solve2();

  std::cout << "+--- --- --- --- --- --- --- --- --- --- --- ---" << std::endl;
  std::cout << "Task21 - example data" << std::endl;
  Task21 task21(true);
  task21.solve1();
  task21.solve2();
  std::cout << "Task21 - example data" << std::endl;
  Task21 task21b(false);
  task21b.solve1();
  task21b.solve2();

  std::cout << "+--- --- --- --- --- --- --- --- --- --- --- ---" << std::endl;
  std::cout << "Task22 - example data" << std::endl;
  Task22 task22(true);
  task22.solve1();
  task22.solve2();
  std::cout << "Task22 - example data" << std::endl;
  Task22 task22b(false);
  task22b.solve1();
  task22b.solve2();

  std::cout << "+--- --- --- --- --- --- --- --- --- --- --- ---" << std::endl;
  std::cout << "Task23 - example data" << std::endl;
  Task23 task23(true);
  task23.solve1();
  task23.solve2();
  std::cout << "Task23 - example data" << std::endl;
  Task23 task23b(false);
  task23b.solve1();
  task23b.solve2();

  std::cout << "+--- --- --- --- --- --- --- --- --- --- --- ---" << std::endl;
  std::cout << "Task24 - example data" << std::endl;
  Task24 task24(true);
  task24.solve1();
  task24.solve2();
  std::cout << "Task24 - example data" << std::endl;
  Task24 task24b(false);
  task24b.solve1();
  task24b.solve2();

  std::cout << "+--- --- --- --- --- --- --- --- --- --- --- ---" << std::endl;
  std::cout << "Task25 - example data" << std::endl;
  Task25 task25(true);
  task25.solve1();
  task25.solve2();
  std::cout << "Task25 - example data" << std::endl;
  Task25 task25b(false);
  task25b.solve1();
  task25b.solve2();
}
