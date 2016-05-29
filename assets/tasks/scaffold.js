module.exports = function (gulp, plugins, config) {
    return plugins.shell.task([
            'mkdir '+ config.distribution,
            'mkdir '+ config.distribution +'/fonts',
            'mkdir '+ config.distribution + '/images',
            'mkdir '+ config.distribution + '/scripts',
            'mkdir '+ config.distribution + '/styles'
    ]); 
};

