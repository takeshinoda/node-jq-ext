import 'babel-register'
import 'babel-polyfill'
import child_process from 'child_process'
import gulp    from 'gulp'
import babel   from 'gulp-babel'
import mocha   from 'gulp-mocha'
import runSequence from 'run-sequence'

const SOURCES    = ['src/**/*.js']
const TEST_FILES = ['test/**/*_test.js', '!test/fixtures/*.js']

gulp.task('test', () => {
  return gulp.src(TEST_FILES)
             //.pipe(mocha({ timeout: 25000, reporter: 'nyan' }))
             .pipe(mocha({ timeout: 25000, reporter: 'dot' }))
})

gulp.task('gyp_configure', (done) => {
  child_process.spawn('node-gyp', ['configure'], { stdio: 'inherit' }).on('close', done);
})

gulp.task('gyp_build', (done) => {
  child_process.spawn('node-gyp', ['build'], { stdio: 'inherit' }).on('close', done);
})

gulp.task('build', (done) => runSequence('gyp_configure', 'gyp_build', done))

gulp.task('default', (done) => runSequence('compile', 'test', done))

