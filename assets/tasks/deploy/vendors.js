module.exports = function (gulp, plugins, config) {
    return function () {
        gulp.src(config.distribution + 'vendors/*.css')
            .pipe(plugins.autoprefixer(config.autoprefixer))
            .pipe(plugins.csso())
            .pipe(gulp.dest(config.deploy + 'vendors/'))
            .on('error', plugins.util.log)


         gulp.src(config.distribution + 'vendors/*.js')
            .pipe(plugins.uglify())
            .pipe(gulp.dest(config.deploy + 'vendors/'))
            .on('error', plugins.util.log)
    };
};
