# Tutorial SCPROG in Summer Term 2021

In the course SCPROG - Scientific Programming with C++ - in summer term 2021 we
are working in the exercises with *git* - a modern version control system / source
code management system - to provide assignments and for you to upload solutions.
Using git allows you to monitor and control your changes to files and using GitLab
as version control platform allows us to easily view and comment on submitted
exercises. Learning *git* is part of the course.

We will give you an introduction to *git* in the first tutorials. See also the
additional references listed below if you want to start early or want to dive deeper
into version control systems.

## How to submit an exercise solution

Solutions to exercises must be submitted to the tutorial repository in order to get
them reviewed. We follow a classical development pattern found in scientific code
development groups: 1. create a new branch for your changes (e.g. the new solutions),
2. upload that branch to the repository and create a Merge request, 3. The Merge
request gets reviewed, maybe need further updates, and eventually gets merged into
the master/main branch.

The submission pattern, as described below, is thus not a simple online education
procedure, but extracted from real live projects. The difference is that we all
work on the same tasks simultaneousely. Eventually only one solution can be merged.
A proper solution is selected from the submitted solutions and integrated (merged)
into the main branch in order to build up a reference solution repository.

We all work together in the same repository, but everyone has its own local repository.
Thus, whenever you have added files or changed some lines in code and you have commited
these changes to your local repository they are safe. If something goes wrong nearly
everything can be recovered and undone. First, check the status of your local repo, using
`git status` and see in which branch you are and which files are changed or unstaged.
You can revert changes, rename branches, or go back to any state previously commited
to your local repository. See the git reference/tutorial for details.

### Submission procedure

Please follow the steps carefully. If any questions arise, ask in the matrix chat.
You should always start with a clean repository. Step 0 should thus be performed
before each new exercise is worked on (or after finishing an exercise). It commits
all leftover changes and downloads updates from the remote repository so that you
start from the latest state.


0. Before you start, check for updates of the remote master branch. First, commit
   all your local changes, change to the master branch, and pull any updates:

   ```bash
   git status                 # optional: See any modified and unstaged files
   git add <files>...         # optional: Add changed/unstaged files to staging area
   git commit -m "<note>"     # optional: Commit changes with log message "<note>"
   git checkout master        # Change to the master branch
   git pull                   # Download all remote changes and merge with master branch
   ```

1. Create a new branch for each exercise. The name of that branch must be
   `<identity>/exercise<nr>` where `<identity>` is your username and `<nr>` the
   number of the exercise. This naming scheme is important in order to identify
   your submission and not to have name clashes by many submissions of the same
   exercise.

   Always create a new branch from the (updated) `master` branch:

   ```bash
   git checkout -b <identity>/exercise<nr> master
   ```

   We will upload each week a new directory to the master branch for each new
   exercise containing the exercise sheed and maybe some material. This will be
   the basis for the solution branch.

2. Add your solution to the corresponding exercise solution folder, `exercise<nr>/`,
   in form of source files and header files, optionally a description file, and
   other auxiliary files that are requested in the exercise tasks.

3. Add your modified files to your local repository by using `git add` and `git commit`:

   ```bash
   git add file1 file2 file3...
   git commit -m "description of what is submitted/changed"
   ```

   In the commit message belongs a short summary of what you have worked on, e.g.,
   `"Function foo() and bar() combined to foo_bar()"` or `"File exercise2.3.cc
   containing the task 2.3 added"`.

4. Continue the development of the solution and repeat steps 3 and 4 until finished.

5. Push your changes to the online repository.

   ```bash
   git push origin <identity>/exercise<nr>
   ```

   This will synchronize your local branch with an automatically created online
   branch in the repository. This makes your local branch public and allows to
   create Merge requests.

6. Create a *Merge request* if you want to get your changes reviewed. Therefore,
   open GitLab, go to the project `scprog/so2021-tutorial` repository page, open
   the menu `Repository -> Branches`, choose your uploaded branch
   `<identity>/exercise<nr>`, and click on *Merge request*. In the title, add the
   exercise number and your name, e.g. "Exercise 4: Simon Praetorius". Add a
   meaningful description of what you have done. This may include details on how
   to run and test your code. Finally, choose the tutor (@spraetor) as *Reviewer*.

   The title again is important for us to identity your submission.

7. In case you want to test the Merge request procedure, but do not yet want to
   get a review, or if you are in the process of developing your solution, add
   the prefix "WIP:" (Work-In-Progress) or "Draft:" to the title. This can be
   changed when ready using the button "Mark as ready" or by removing the prefix
   from the title.

8. You will get comments in the code and in the Merge Request as review. This helps to
   improve your programming skills and the quality of your future submissions.

   We will select one of the submissions to be merged into the master branch. In this
   way we build up a collection of reference solutions for all the exercises.


## Style Guidelines
All programs you submit should follow basic programming rules like the following:

- **Formatting**
  - Put each instruction on a separate line (two lines if it is very large)
  - Use spaces to separate variable names, functions and operators
  - Indent your lines to visually mark different lines belonging to different scopes
- **Variable names**
  - The name should reflect the purpose of the variable
  - Variable names start with a lowercase letter, types with an uppercase letter
  - The rest of the name format for identifiers is up to you
  - Simple counting integers and similar variables are exceptions
- **Comments**
  - Comments allow others to understand your intentions
  - Tutors can only give you points if they understand what you were trying to do
  - *Guideline:* one comment per class, per function, per algorithm subtask, per tricky or "exotic" source line
  - Don't comment to much either, this may visually drown the actual code or diverge from what is actually coded (!)
  - Leave out trivial comments ("This is the constructor")
- **Language constructs**
  - You may use any construct you want, even if it has not yet been introduced in the lecture
  - Avoid constructs that have been superseded by better alternatives in the lecture
  - Declare variables and references as `const` where it is possible
  - Separate interface and implementation by correctly using public and private
  - Use smart pointers instead of raw pointers once the lecture has introduced them

Optionally, see [Google C++ Style Guide](http://google.github.io/styleguide/cppguide.html) for
more rules and guidelines on the coding style. Also, see the
[C++ Core Guidelines](https://github.com/isocpp/CppCoreGuidelines/blob/master/CppCoreGuidelines.md)
for a comprehensive list of best practice programming rules for C++.


## Sandbox directory

Use the directory `sandbox/` for experiments to store files that should not be
uploaded to the repository at all. This directory is *ignored* in the `.gitignore`
file and will thus not be put in the staging area and not be commited.


## Introduction to Git

If you are not familiar with [Git](https://git-scm.com/docs) or [GitLab](https://docs.gitlab.com/)
you can find an introduction either on
- [Pro Git](https://git-scm.com/book) Online book
- [Oh my Git!](https://ohmygit.org/) An open source game about learning Git!
- [Git Cheat Sheet](https://github.github.com/training-kit/downloads/github-git-cheat-sheet.pdf)
- [Version control in VS Code](https://code.visualstudio.com/docs/introvideos/versioncontrol)

## FAQ

Here questions and answers will be collected for common problems. A general
recommendation is  to check the status of all files with `git status`, and to
follow the instruction given by the git error messages if they occure. Searching
for the error message in, e.g., google, will often give you a proper answer for
the problem, e.g. on [stackoverflow.com](https://stackoverflow.com/).
