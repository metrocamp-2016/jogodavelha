module.exports = function (gulp, plugins, config) {
    return function () {
        gulp.src(config.vendors.head)
            .pipe(gulp.dest(config.distribution + 'vendors/'))
            .on('error', plugins.util.log);

         gulp.src(config.vendors.javascript)
            .pipe(plugins.concat('vendor.js'))
            .pipe(gulp.dest(config.distribution + 'vendors/'))
            .on('error', plugins.util.log);

       
         gulp.src(config.vendors.style)
            .pipe(plugins.concat('vendor.css'))
            .pipe(gulp.dest(config.distribution + 'vendors/'))
            .on('error', plugins.util.log);

         gulp.src(config.vendors.font)
            .pipe(gulp.dest(config.distribution + 'fonts/'));
    };
};
