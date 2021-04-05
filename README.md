# Tutorial SCPROG in Summer Term 2021

In the course SCPROG - Scientific Programming with C++ - in summer term 2021 we
are working in the exercises with git - a modern version control system / source
code management system - to provide assignments and for you to upload solutions.
Using git allows you to monitor and control your changes to files and using GitLab
as version control platform allows us to easily view and comment on submitted
exercises.

## How to submit an exercise solution

Solutions to exercises can be submitted to the tutorial repository in order to get
it reviewed. We follow a classical development pattern: 1. create a new branch
for your changes (the new solutions), 2. upload that branch to the repository and
create a Merge request, 3. One of the submissions is merged by the Tutor after
the review phase.

You should always start with a clean repository. Step 0 should thus be performed
before each new exercise is worked on (or after finishing an exercise). It commits
all leftover changes and downloads updates from the remote repository so that you
start from the latest state.

If something goes wrong, you first should check the status of your local repo, using
`git status` and see in which branch you are and which files are changed or unstaged.
You can revert changes or rename branches easily. See the git reference/tutorial
for details.

### Submission procedure

Please follow the steps carefully. If any questions arise, ask in the matrix chat.

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
   number of the exercise. Always create a new branch from the `master` branch:

   ```bash
   git checkout -b <identity>/exercise<nr> master
   ```

2. Add your solution to the corresponding exercise solution folder, `exercise<nr>/`,
   in form of source fildes and header files, optionally a description file (e.g.
   a markdown file), and optionally a *Makefile* or *CMakeLists.txt* (see later exercises).

3. Add your added files to your local repository using `git add` and `git commit`:

   ```bash
   git add file1 file2 file3...
   git commit -m "description of what is submitted/changed"
   ```

4. Continue the development of the solution and repeat steps 3 and 4 until finished

5. Push your changes to the online repository.

   ```bash
   git push origin <identity>/exercise<nr>
   ```

6. Create a *Merge request* if you want to get your changes reviewed. Therefore,
   open GitLab, go to the project `scprog/so2021-tutorial` repository page, open
   the menu `Repository->Branches` and choose your uploaded branch
   `<identity>/exercise<nr>`, click on *Merge request*. In the title, add the
   exercise number and your name, e.g. "Exercise 4: Simon Praetorius". Add a
   meaningful description of what you have done. This may include details on how
   to run and test your code. Choose the tutor (@spraetor) as *Reviewer*

7. In case you want to test the Merge request procedure, but do not yet want to
   get a review, or if you are in the process of developing your solution, add
   the prefix "WIP:" (Work-In-Progress) or "Draft:" to the title. This can be
   changed when ready using the button "Mark as ready" or by removing the prefix
   from the title.

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

## FAQ

Here questions and answers will be collected for common problems. A general
recommendation is  to check the status of all files with `git status`, and to
follow the instruction given by the git error messages if they occure. Searching
for the error message in, e.g., google, will often give you a proper answer for
the problem, e.g. on stackoverflow.com.