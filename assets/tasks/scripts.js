module.exports = function (gulp, plugins, config) {
    return function () {
        gulp.src(config.source + "scripts/main.js")
            .pipe(plugins.concat('app.js'))
            .pipe(plugins.browserify())
            .pipe(gulp.dest(config.distribution + 'scripts/'))
            .on('error', plugins.util.log)
            .pipe(plugins.livereload());

    };
};
