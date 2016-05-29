module.exports = function (gulp, plugins, config) {
    return function () {
        gulp.src(config.distribution + 'images/*.{jpg,png,webp,gif}')
            //.pipe(plugins.tinypng(config.tinypng.token))
            .pipe(gulp.dest(config.deploy + 'images/' ));
    };
};
