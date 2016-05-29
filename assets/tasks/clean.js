module.exports = function (gulp, plugins, config) {
    return plugins.shell.task([
            'rm -rf ' + config.distribution
    ]); 
};

