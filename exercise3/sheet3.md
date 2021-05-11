# Exercise sheet 3 (May 12th 2021)

## Task 1 (Operators)
What is the meaning of the following arithmetic expressions? To illustrate which sub-expression is evaluated first, add brackets!

```c++
(a) x / y * z             (g) z-y-x?x+y+z:x-y-z
(b) x * y++ / -z          (h) z<<x>>y
(c) x^2 + y^2             (i) z>>x<<y
(d) ++x * x++             (j) x||y||z
(e) *&x*y&&z              (k) ++x*=y++
(f) x+++x                 (l) -~x^x
```

What is the value of the expressions with the following value of the variables?

```c++
int x = 3;
int y = 2;
int z = 5;
```

What is the value of the variables `x`, `y`, and `z` after evaluating the expression?

First, try to evaluate by hand, then check your results by implementing the expressions.

### Resources
- [cppreference:expressions](https://en.cppreference.com/w/cpp/language/expressions#Operators),
  [cppreference:operator_precedence](https://en.cppreference.com/w/cpp/language/operator_precedence)
- [Wikibook:Operatoren](https://de.wikibooks.org/wiki/C%2B%2B-Programmierung:_Operatoren)


## Task 2 (Structs)
A `struct` in C++ is a type of record encapsulating data (and methods that act on this data).
The most simple structs are those just containing data. In this sense a `struct` is a compound data type.
Each data type has a size in memory. This can be evaluated with `sizeof(TYPE)` or `sizeof(EXPRESSION)`.
The actual total size of the data type might depend on its members and the order of its members.

1. Define a `struct` with a member of each of the types `bool`, `char`, `int`, `long`, `double`, and `long double`.
Order the members so as to get the largest size of the struct and the smallest size of the struct.
2. What is the size of an empty `struct` without any member variables? Why?

### Note
- While you might get different sizes of the struct type when reordering the members, this saving seems to be small, but
  when you allocate a vector of that many of these types, you might end up with large memory savings.
- But, be aware of the fact that the order of members does not only affect the memory size but also the
  read and write performance when accessing the members. See the blog post of Jonas Devlieghere from below.

### Resources
- [cppreference:class](https://en.cppreference.com/w/cpp/language/class)
- https://jonasdevlieghere.com/order-your-members/


## Task 3 (Code formatting)
It is recommended to follow some code style guidelines. Be consistent with naming, indentation, brackets, etc.
This formatting of the code does not influence the compiler. A program can read any valid source code.
But it gives you and your coworkers (or you in the future when you reopen some old code) as a human readers
some benefit. Style your code consistently from the first line!

A minimal guideline is given in the README. But there is more. And there are different common styles.
Sometimes you get code from someone else and need to read/understand it. A good starting point is to
transform the code to your code style. This can be automated.

In `material/task3.cc` you can find a horribly complicated unreadable code. Reformat it manually or using some tools:

- [clang-format](https://clang.llvm.org/docs/ClangFormat.html)
- [astyle](http://astyle.sourceforge.net/)
- [uncrustify](http://uncrustify.sourceforge.net/)

### Resources
- [Google code style](https://google.github.io/styleguide/cppguide.html),
- [Indentation styles](https://en.wikipedia.org/wiki/Indentation_style)
- [Cpp Core guidelines](https://github.com/isocpp/CppCoreGuidelines/blob/master/CppCoreGuidelines.md)


## Task 4 (Dual numbers) - Submit for review :pencil:
In algebra, the dual numbers are a hypercomplex number system first introduced in the 19th century.
They are expressions of the form $`\tilde{x}=a + b\varepsilon`$, where $`a`$ and $`b`$ are real numbers, and $`\varepsilon`$
is a symbol taken to satisfy $`\varepsilon^2 = 0`$

Dual numbers can be added componentwise, and multiplied by the formula

```math
  (a+b\varepsilon)(c+d\varepsilon)=ac+(ad+bc)\varepsilon,
```

which follows from the property $`\varepsilon^2 = 0`$ and the fact that multiplication is a bilinear operation. ([Text extracted from Wikipedia][1])

1. Implement the dual numbers as pair of `double`s, i.e., provide a `struct DualNumber` with two members of type `double`.
2. Provide mathematical operations for `+, -, *, /` in form of functions
    - `add: DualNumber x DualNumber -> DualNumber`
    - `sub: DualNumber x DualNumber -> DualNumber`
    - `mul: DualNumber x DualNumber -> DualNumber`
    - `div: DualNumber x DualNumber -> DualNumber`
3. In your `main()` introduce constants `one` and `eps` representing the `DualNumber`s $`1`$ and
   $`\varepsilon`$, respectively. Test that the following identities hold:

```math
    { 1\cdot \varepsilon =\varepsilon \cdot 1=\varepsilon }\\
    { 1\cdot (1\cdot \varepsilon )=1\cdot \varepsilon =(1\cdot 1)\cdot \varepsilon =\varepsilon }\\
    { 1\cdot (\varepsilon \cdot \varepsilon )=1\cdot 0=0=\varepsilon \cdot \varepsilon =(1\cdot \varepsilon )\cdot \varepsilon }
```

4. Compute the follow polynomial expressions for $`\tilde{x}=a + b\varepsilon`$:

```math
f(\tilde{x}) = 5\tilde{x}^4-2\tilde{x}^2+7
```

and evaluate for $`a=3`$ and $`b=1`$. Compare with $`f(a)`$ and $`f'(a)`$.

5. (optional) Instead of writing functions with the names `add`, `sub`, `mul`, and `div`, implement functions with
   the names `operator+`, `operator-`, `operator*` and `operator/`. How can you evaluate the expression in 4. now?

[1]: https://en.wikipedia.org/wiki/Dual_number

### Resources
- https://en.wikipedia.org/wiki/Dual_number
- [cppreference:struct](https://en.cppreference.com/w/cpp/language/class)
- [cppreference:operators](https://en.cppreference.com/w/cpp/language/operators)

### Submission
This exercise can be submitted for review. Please follow the general instructions given in the [README.md](/README.md)
page. In summary: 1. create a new branch `<zih-id>/exercise3`, 2. inside the folder `exercise3/` add
your solution: `task4.cc`, 3. `git add` and `git commit` your added and changed files, 4. push your
branch to the remote repository by `git push origin <zih-id>/exercise3`, 5. create a merge request.

**Deadline for the submission: end of 2021/05/19**


## Extra Task 5 (Duff's device)
What does the following example do?
```c++
int func (std::vector<int> const& data)
{
  int to = 0;
  int count = data.size();
  int n = (count + 7)/8;
  int i = 0;
  switch (count % 8) {
    case 0: do { to += data[i++];
    case 7: to += data[i++];
    case 6: to += data[i++];
    case 5: to += data[i++];
    case 4: to += data[i++];
    case 3: to += data[i++];
    case 2: to += data[i++];
    case 1: to += data[i++];
    } while (--n > 0);
  }
  return to;
}
```
Why would anyone write something like that? No, this is not recommended as good style!

### Resources
- [Wikipedia:Duffs_Device](https://en.wikipedia.org/wiki/Duff%27s_device)
- [mailinglist post by Tom Duff](https://www.lysator.liu.se/c/duffs-device.html)
- Search for Loop unrolling for more information.