module.exports = function () {
    return  {
        source : 'src/',
        distribution : 'dist/',
        deploy : 'deploy/',
        autoprefixer : {
            browsers: ['last 2 version', 'safari 5', 'ie 8', 'ie 9', 'opera 12.1', 'ios 6', 'android 4'],
            cascade:  true
        },
        imagemmin : { optimizationLevel: 5, progressive: true, interlaced: true },
        tinypng: {
            token : 'y990ySWpkgpYXj1Zb-xImMLGQW-3Ik4x' 
        },
        vendors : {
            head : [
                'bower_components/html5shiv/dist/html5shiv.js', 
                'bower_components/modernizr/modernizr.js' 
            ],
            javascript : [
                'bower_components/bLazy/blazy.js', 
                'bower_components/jquery/dist/jquery.js',
                'bower_components/gsap/TweenLite.min.min.js',
                'bower_components/gsap/TimelineLite.min.js', 
                'bower_components/angular/angular.min.js', 
                'bower_components/angular-animate/angular-animate.min.js', 
                'bower_components/angular-cookies/angular-cookies.min.js', 
                'bower_components/angular-sanitize/angular-sanitize.min.js', 
                'bower_components/angular-route/angular-route.min.js', 
                'bower_components/angular-resource/angular-resource.min.js', 
                'bower_components/fastclick/lib/fastclick.js', 
                'bower_components/owlcarousel/owl-carousel/owl.carousel.min.js',
                'bower_components/Slidebars/dist/slidebars.min.js'

            ],
            style : [
                'bower_components/normalize-css/normalize.css',
                'bower_components/font-awesome/css/font-awesome.min.css',
                'bower_components/owlcarousel/owl-carousel/owl.carousel.css',
                'bower_components/owlcarousel/owl-carousel/owl.theme.css',
                'bower_components/owlcarousel/owl-carousel/owl.transitions.js',
                'bower_components/Slidebars/dist/slidebars.min.css'
            ],
            font : [
                'bower_components/font-awesome/fonts/*'
            ]
        },
        methods : {
            functions : {
                division : function (number1, number2) {
                    return Math.ceil(number1 / number2);
                }     
            }
        }
    }
};
