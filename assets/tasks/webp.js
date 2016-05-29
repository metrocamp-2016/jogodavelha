module.exports = function (gulp, plugins, config) {
    return function () {
        gulp.src(config.source + 'images/*.{jpg,png}')
            .pipe(plugins.webp())
            .pipe(gulp.dest(config.source + 'images/'));
    };
};

