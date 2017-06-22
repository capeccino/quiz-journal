# Improve: Quiz Journal

The purpose of Improve: Quiz Journal is to provide a means for self-analysis, which facilitates self-improvement. A "Quiz Journal" consists of user created questions that will be answered on a regular basis. If created with care, a journal of such questions can break down a bigger topic so that the fine details can easily be tracked and analyzed. This software provides the ability to create such journals, add entries, and analyze answer sets.

### Example

A user creates a "personal interactions" journal that consists of two basic questions:

* What was the most positive interaction I was a part of today?
* What was the most negative interaction I was a part of today?

After a few weeks of consistently inputting answers to these questions, the user can run analysis tools for each question to determine names, locations, situational words, states of mind, etc. that come up frequently. The user can then determine the factors most likely to effect a change to the positive. 

## Prerequisites

This software is in development using the Qt Framework version 5.9. If you would like to contribute or otherwise mess around with it, you'll need to install Qt 5.9, as well as a C++ compiler. I have been using Qt Creator 4.3 as my IDE, with MSVC 2017 x64 as my compiler, but other C++ development environments would probably suffice if you know what you're doing. 

If you're using Qt Creator, you will need to manually create a folder called DBs in the top level of the build directory for your current setting (debug/release). For other environments, you may have to experiment to determine exactly where to create the folder. You'll know it is successful when, directly after starting the program, a file called IQJ_DB is created in the folder. 

## Current State

As of June 22, 2017, Improve: Quiz Journal is an early prototype. A user is able to create a basic journal of questions and add entries by answering those questions. Information is stored in SQLite databases (SQLite is included with Qt). There are no analysis tools at this time.

## Path of Improvement

1. Reassess current code base in an effort to achieve the best possible design.
2. Add some analysis capabilities.
3. Improve user interface with stylesheets so that it doesn't look like it was designed in 1993. 
4. Complete unimplemented features such as import/export of journals/questions.
5. Provide better facilities for editing journals, questions, entries, answers.
6. Provide additional elements for a user to choose as part of questions (combo boxes, check boxes, etc).
7. Provide a means for adding logic to entry flow, such that the answer to a question can determine which questions come next.
8. Improve and expand current features.

## Contributing

This software is in an early state, so there is a lot of potential for improvement in just about every aspect. All contributions are welcome.
Additionally, any advice, criticisms, pointing out of mistakes, etc. would be greatly appreciated. I'm certain there are aspects of the code and design that are not yet ideal. My mission is to always become better than I am.
 
## License

This project is licensed under LGPL version 3 in accordance with the licensing requirements attached to the open source version of the Qt Framework.