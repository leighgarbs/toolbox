GITLAB_URL_TOOLBOX = 'http://gitlab.dmz/leighgarbs/toolbox.git'

STAGES = ['Checkout',
          'cppcheck',
          'Unit Tests - Release Build',
          'Unit Tests - Debug Build',
          'Valgrind',
          'Clang Static Analyzer']

properties([[$class: 'GitLabConnectionProperty',
            gitLabConnection: 'gitlab.dmz'],
            pipelineTriggers([[$class: 'GitLabPushTrigger',
                              triggerOnPush: true,
                              triggerOnMergeRequest: true,
                              skipWorkInProgressMergeRequest: true,
                              pendingBuildName: STAGES[0]]])])

gitlabBuilds(builds: STAGES) {

node () {

stage (STAGES[0]) { gitlabCommitStatus(name: STAGES[0]) {

  deleteDir()

  checkout changelog: true, poll: true, scm: [$class: 'GitSCM',
    branches: [[name: env.BRANCH_NAME]],
    browser: [$class: 'GitLab',
             repoUrl: GITLAB_URL_TOOLBOX,
             version: '11.0'],
    extensions: [[$class: 'SubmoduleOption',
                disableSubmodules: false,
                parentCredentials: false,
                recursiveSubmodules: false,
                reference: '',
                trackingSubmodules: false]],
    submoduleCfg: [],
    userRemoteConfigs: [[credentialsId: '',
                       url: GITLAB_URL_TOOLBOX]]]

  sh '''
    git clone http://gitlab.dmz/leighgarbs/bin.git $TEMP_BIN
  '''

}}

stage (STAGES[1]) { gitlabCommitStatus(name: STAGES[1]) {

  def shellReturnStatus = sh returnStatus: true, script: '''
    $TEMP_BIN/run-cppcheck -J --suppress=unusedFunction .
  '''

  if(shellReturnStatus == 1)
  {
    currentBuild.result = 'UNSTABLE'
  }

}}

if (currentBuild.result == 'UNSTABLE')
{
  updateGitlabCommitStatus(name: STAGES[1], state: 'failed')
}

stage (STAGES[2]) { gitlabCommitStatus(name: STAGES[2]) {

  sh '''
    $TEMP_BIN/run-cmake --release .
    make unittests

    for file in unittests/*.ut; do $file; done
  '''

  warnings canComputeNew: false,
           canResolveRelativePaths: false,
           categoriesPattern: '',
           consoleParsers: [[parserName: 'GNU Make + GNU C Compiler (gcc)']]

}}

stage (STAGES[3]) { gitlabCommitStatus(name: STAGES[3]) {

  sh '''
    $TEMP_BIN/run-cmake --debug .
    make unittests

    for file in unittests/*.ut; do $file; done
  '''

}}

stage (STAGES[4]) { gitlabCommitStatus(name: STAGES[4]) {

    step([$class: 'ValgrindBuilder',
      childSilentAfterFork: false,
      excludePattern: '',
      generateSuppressions: false,
      ignoreExitCode: false,
      includePattern: 'unittests/*.ut',
      outputDirectory: '',
      outputFileEnding: '.valgrind.xml',
      programOptions: '',
      removeOldReports: false,
      suppressionFiles: '',
      tool: [$class: 'ValgrindToolMemcheck',
            leakCheckLevel: 'full',
            showReachable: false,
            trackOrigins: true,
            undefinedValueErrors: true],
      traceChildren: false,
      valgrindExecutable: '',
      valgrindOptions: '',
      workingDirectory: ''])

    step([$class: 'ValgrindPublisher',
      failBuildOnInvalidReports: false,
      failBuildOnMissingReports: false,
      failThresholdDefinitelyLost: '',
      failThresholdInvalidReadWrite: '',
      failThresholdTotal: '',
      pattern: '*.valgrind.xml',
      publishResultsForAbortedBuilds: false,
      publishResultsForFailedBuilds: false,
      sourceSubstitutionPaths: '',
      unstableThresholdDefinitelyLost: '0',
      unstableThresholdInvalidReadWrite: '0',
      unstableThresholdTotal: '0'])

}}

if (currentBuild.result == 'UNSTABLE')
{
  updateGitlabCommitStatus(name: STAGES[4], state: 'failed')
}

stage (STAGES[5]) { gitlabCommitStatus(name: STAGES[5]) {

  sh '''
    rm CMakeCache.txt
    rm -rf CMakeFiles
    scan-build $TEMP_BIN/run-cmake --debug .
    scan-build -o clangScanBuildReports -v -v --use-cc clang --use-analyzer=/usr/bin/clang make
  '''

}}

}

}
