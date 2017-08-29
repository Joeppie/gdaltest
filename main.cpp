#include <memory>
#include "ogrsf_frmts.h"

int main()
{
    const char *pszDriverName = "ESRI Shapefile";
    OGRSFDriver *poDriver;

    OGRRegisterAll();

    poDriver = OGRSFDriverRegistrar::GetRegistrar()->GetDriverByName(
            pszDriverName );
    if( poDriver == NULL )
    {
        printf( "%s driver not available.\n", pszDriverName );
        exit( 1 );
    }

    //OGRDataSource *poDS;
    std::shared_ptr<OGRDataSource> poDS(poDriver->CreateDataSource( "point_out.shp", NULL ),OGRDataSource::DestroyDataSource);

   // poDS = poDriver->CreateDataSource( "point_out.shp", NULL );
    if( poDS == NULL )
    {
        printf( "Creation of output file failed.\n" );
        exit( 1 );
    }

    OGRLayer *poLayer;

    poLayer = poDS->CreateLayer( "point_out", NULL, wkbPoint, NULL );
    if( poLayer == NULL )
    {
        printf( "Layer creation failed.\n" );
        exit( 1 );
    }

    OGRFieldDefn oField( "Name", OFTString);

    oField.SetWidth(32);

    if( poLayer->CreateField( &oField ) != OGRERR_NONE )
    {
        printf( "Creating Name field failed.\n" );
        exit( 1 );
    }

    double x = 92535.369821, y = 437371.911496;
    char szName[33] =  "well howdy there.";

/*    while( !feof(stdin)
           && fscanf( stdin, "%lf,%lf,%32s", &x, &y, szName ) == 3 )*/
    {
        //OGRFeature *poFeature;
        std::shared_ptr<OGRFeature>poFeature(OGRFeature::CreateFeature( poLayer->GetLayerDefn()),OGRFeature::DestroyFeature);
        //szName =  "hello";

        //poFeature = OGRFeature::CreateFeature( poLayer->GetLayerDefn() );
        poFeature->SetField( "Name", szName );

        OGRPoint pt;

        pt.setX( x );
        pt.setY( y );

        poFeature->SetGeometry( &pt );

        if( poLayer->CreateFeature( poFeature.get() ) != OGRERR_NONE )
        {
            printf( "Failed to create feature in shapefile.\n" );
            exit( 1 );
        }


        //OGRFeature::DestroyFeature( poFeature );
    }

    //OGRDataSource::DestroyDataSource( poDS );
}