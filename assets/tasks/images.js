module.exports = function (gulp, plugins, config) {
    return function () {
        gulp.src(config.source + 'images/*.{jpg,png}')
            .pipe(plugins.imagemin(config.imagemin))
            .pipe(gulp.dest(config.distribution + 'images/' ));
    };
};
