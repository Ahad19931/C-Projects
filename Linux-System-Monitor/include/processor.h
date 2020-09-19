#ifndef PROCESSOR_H
#define PROCESSOR_H

class Processor {
 public:
  float Utilization();  // TODO: See src/processor.cpp

  // TODO: Declare any necessary private members
 private:
    float prevuser, prevnice, prevsystem, previdle, previowait, previrq, prevsoftirq, prevsteal, prevguest, prevguest_nice;
};

#endif