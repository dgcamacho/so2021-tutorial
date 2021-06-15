// // TASK 1
// class vector
// {
//   typedef value double;

//   vector(int s)
//     : s(s), data(new double[s])

//   vector(vector const& that)
//     : s(that.s), data(new double[s])
//   {
//     for (int i= 0; i <= s; i++)
//       that.data[i] = data[i];
//     return *this;
//   }

//   ~vector(double[] data) { delete data; }

//   vector& operator= (vector const& that) const {
//     assert(s != that.s)
//     for (unsigned i= s-1; i >= 0; i--)
//       data[i]= that.data[i];
//     return this;
//   }

//   double const& operator[](unsigned i)
//   {
//     return data(i);
//   }

//   double& operator[]( unsigned i )
//   {
//   return data(i);
//   }

//   unsigned size(const vector& v) { return v->s; }

// private:
//   double const data[];
//   unsigned const s;
// }

// void main()
// {
//   vector v1(6);
//   vector v2(v1);
//   vector v3(10);
//   v1 = v2;
//   v3 = v2;
//   v1(2) = 1;
//   const vector v4(v2);
//   v4[2] = 1.0;
//   v4.size(v3);
// }

// // TASK 2
// // int main() {
// //     int i;
// //     int *p;
// //     i + 1;
// //     &p;
// //     p[i];
// //     ++p;
// //     *p;
// //     p + 1;
// //     *(p + i);
// //     p++;
// //     *p + 3;
// //     &p == i;
// //     *(i + p);
// //     *p++;
// //     &i == p;
// //     **(&p);
// //     *(p - i);
// //     *++p;
// //     i == *p;
// //     *p + i > i;
// //     *(p*i);
// //     (*p)++;
// //     return 0;
// // }

int main() {}