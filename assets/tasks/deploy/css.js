module.exports = function (gulp, plugins, config) {
    return function () {
        gulp.src(config.distribution + 'styles/*.css')
            .pipe(plugins.autoprefixer(config.autoprefixer))
            .pipe(plugins.csso())
            .pipe(gulp.dest(config.deploy + 'styles/'))
            .on('error', plugins.util.log)
    };
};
