#!groovy

@Library(value="jenkins-sl@badbuild-fix")

stages = [

  [name: 'Checkout',
   body: stageCheckout,
   args:  ["http://gitlab.dmz/leighgarbs/toolbox.git"]],

  [name: 'cppcheck',
   body: stageCppcheck,
   args: ["--suppress=unusedFunction"]],

  [name: 'Release Build',
   body: stageBuild,
   args: ['release', 'tests']],

  [name: 'Release Tests',
   body: stageTests,
   args: []],

  [name: 'Debug Build',
   body: stageBuild,
   args: ['debug', 'tests']],

  [name: 'Debug Tests',
   body: stageTests,
   args: []],

  [name: 'Valgrind',
   body: stageValgrind,
   args: []],

  [name: 'Clang Static Analyzer',
   body: stageClangStaticAnalysis,
   args: []],

  [name: 'Detect Warnings',
   body: stageDetectWarnings,
   args: []]

]

doStages(stages)
