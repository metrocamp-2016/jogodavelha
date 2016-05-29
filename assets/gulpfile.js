var config = {}, 
    gulp = require('gulp'),
    plugins = require('gulp-load-plugins')(),
    runSequence = require('run-sequence');

plugins.precss = require('precss');
plugins.grid = require('lost');
plugins.functions = require('postcss-functions');
config = require('./task.config')();

function getTask(task) {
    return require('./tasks/' + task)(gulp, plugins, config);
}
//Create Structure of Distribution folder
gulp.task('structs:dist', ['clean','scaffold']);

//Task of Vendors
gulp.task('vendor', getTask('vendor'));

//Task of DEFAULT
gulp.task('scripts', getTask('scripts'));
gulp.task('css', getTask('postcss'));
gulp.task('images', getTask('images'));
//gulp.task('webp', getTask('webp'));
gulp.task('fonts', getTask('font'));
gulp.task('clean', getTask('clean'));
gulp.task('scaffold', getTask('scaffold'));

gulp.task('basic', ['fonts','images','scripts', 'css']);

gulp.task('default', ['basic'], function () {
    plugins.livereload.listen();
    gulp.watch('src/scripts/**/*.js', ['scripts']);
                                gulp.watch('src/styles/**/*.css', ['css']);
                                                           });

//Task of DEPLOY
gulp.task('deploy:images', ['basic'], getTask('deploy/images'));
gulp.task('deploy:css', ['basic'], getTask('deploy/css'));
gulp.task('deploy:scripts',  ['basic'], getTask('deploy/scripts'));
gulp.task('deploy:vendors',  ['basic'], getTask('deploy/vendors'));
gulp.task('deploy:fonts', getTask('deploy/font'));
gulp.task('deploy', ['deploy:images','deploy:css','deploy:fonts','deploy:scripts', 'deploy:vendors']);

