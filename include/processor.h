#ifndef PROCESSOR_H
#define PROCESSOR_H

class Processor {
 public:
  float Utilization();  // TODO: See src/processor.cpp

  // TODO: Declare any necessary private members
 private:
  unsigned long long PrevIdle{0};
  unsigned long longIdle{0};

  unsigned long longPrevNonIdle{0};
  unsigned long longNonIdle{0};

  unsigned long longPrevTotal{0};
  unsigned long longTotal{0};

  unsigned long longtotald{0};
  unsigned long longidled{0};
};

#endif