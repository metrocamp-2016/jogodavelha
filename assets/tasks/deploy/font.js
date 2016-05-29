module.exports = function (gulp, plugins, config) {
    return function () {
        gulp.src(config.distribution + 'fonts/**/*.*')
            .pipe(gulp.dest(config.deploy + 'fonts/'))
            .on('error', plugins.util.log);
    };
};
