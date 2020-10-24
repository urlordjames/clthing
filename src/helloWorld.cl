__kernel void helloWorld(__global int data[]) {
  data[get_global_id(0)] += 1;
}
