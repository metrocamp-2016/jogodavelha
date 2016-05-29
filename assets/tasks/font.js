module.exports = function (gulp, plugins, config) {
    return function () {
        gulp.src(config.source + 'fonts/**/*.*')
            .pipe(gulp.dest(config.distribution + 'fonts/'))
            .on('error', plugins.util.log);
    };
};
