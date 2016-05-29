module.exports = function (gulp, plugins, config) {
    return function () {
       gulp.src(config.distribution + 'scripts/app.js')
           .pipe(plugins.uglify())
           .pipe(gulp.dest(config.deploy + 'scripts/'))
           .on('error', plugins.util.log);
    };
};
