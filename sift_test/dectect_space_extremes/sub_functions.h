
#include<opencv/cv.h>
#include<opencv/highgui.h>
#include<opencv/cxcore.h>

#define FEATURE_MAX_D 128
/* a(x-u)(x-u) + 2b(x-u)(y-v) + c(y-v)(y-v) = 1
 * x y represent the affine region around the feature*/
struct feature
{
    double x;                       /**< x coord */
    double y;                       /**< y coord */
    double a;
    double b;
    double c;
    double scl;                     /**< scale of a Lowe-style feature */
    double ori;                     /**< orientation of a Lowe-style feature */
    int d;                          /**< descriptor length */
    double descr[FEATURE_MAX_D];    /**< descriptor */
    int type;                       /**< feature type, OXFD or LOWE */
    int category;                   /**< all-purpose feature category */
    struct feature *fwd_match;      /**< matching feature from forward image */
    struct feature *bck_match;      /**< matching feature from backward image */
    struct feature *mdl_match;      /**< matching feature from model */
    CvPoint2D64f img_pt;            /**< location in image */
    CvPoint2D64f mdl_pt;            /**< location in model */
    void *feature_data;             /**< user-definable data*/
};

struct detection_data
{
    int r;
    int c;
    int octv;
    int intvl;
    double subintvl;
    double scl_octv;
};
IplImage* downsample( IplImage* img );
IplImage* convert_to_gray32( IplImage* img );
IplImage* create_init_img( IplImage* img, int img_dbl, double sigma );
IplImage* convert_to_gray32( IplImage* img );
IplImage*** build_gauss_pyr( IplImage* base, int octvs, int intvls, double sigma );
IplImage*** build_dog_pyr( IplImage*** gauss_pyr, int octvs, int intvls );

int is_extremum( IplImage ***dog_pyr, int octv, int intvl, int r, int c );
float pixval32f(IplImage* img, int r, int c);
