module.exports = function (gulp, plugins, config) {
    return function () {
        var processors = [
            plugins.precss(),
            plugins.functions(config.methods),
            plugins.grid()
        ];

        gulp.src(config.source + 'styles/*.css')
            .pipe(plugins.sourcemaps.init())
            .pipe(plugins.postcss(processors))
            .pipe(plugins.autoprefixer(config.autoprefixer))
            .pipe(plugins.sourcemaps.write())
            .pipe(gulp.dest(config.distribution + 'styles/'))
            .on('error', plugins.util.log)
            .pipe(plugins.livereload());
    };
};

