#include <optional>
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <io2d.h>
#include <chrono>
#include "route_model.h"
#include "render.h"
#include "route_planner.h"

using namespace std::experimental;

static std::optional<std::vector<std::byte>> ReadFile(const std::string &path)
{   
    std::ifstream is{path, std::ios::binary | std::ios::ate};
    if( !is )
        return std::nullopt;
    
    auto size = is.tellg();
    std::vector<std::byte> contents(size);    
    
    is.seekg(0);
    is.read((char*)contents.data(), size);

    if( contents.empty() )
        return std::nullopt;
    return std::move(contents);
}


int main(int argc, const char **argv)
{    
    std::string osm_data_file = "";
    if( argc > 1 ) {
        for( int i = 1; i < argc; ++i )
            if( std::string_view{argv[i]} == "-f" && ++i < argc )
                osm_data_file = argv[i];
    }
    else {
        std::cout << "To specify a map file use the following format: " << std::endl;
        std::cout << "Usage: [executable] [-f filename.osm]" << std::endl;
        osm_data_file = "../map2.osm";
    }
    
    std::vector<std::byte> osm_data;
 
    if( osm_data.empty() && !osm_data_file.empty() ) {
        std::cout << "Reading OpenStreetMap data from the following file: " <<  osm_data_file << std::endl;
        auto data = ReadFile(osm_data_file);
        if( !data )
            std::cout << "Failed to read." << std::endl;
        else
            osm_data = std::move(*data);
    }
    
    // TODO 1: Declare floats `start_x`, `start_y`, `end_x`, and `end_y` and get
    // user input for these values using std::cin. Pass the user input to the
    // RoutePlanner object below in place of 10, 10, 90, 90.

    auto start = std::chrono::high_resolution_clock::now();
    // Build Model.
    RouteModel model{osm_data};

    // Create RoutePlanner object and perform A* search.
    RoutePlanner route_planner{model, 10, 10, 80, 80};
    route_planner.AStarSearch();

    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);


    std::cout << "Distance: " << route_planner.GetDistance() << " meters. \n";
    std::cout << "Time taken by function: " << duration.count() << " milliseconds\n"; //401 milliseconds

    // Render results of search.
    Render render{model};


    auto display = io2d::output_surface{900, 770, io2d::format::argb32, io2d::scaling::none, io2d::refresh_style::fixed, 30};
    display.size_change_callback([](io2d::output_surface& surface,auto dim){
        surface.dimensions(dim);
    });



    display.draw_callback([&](io2d::output_surface& surface){
        render.Display(surface);

    });

    display.events_callback(io2d::default_graphics_surfaces::_EventCallBack([&display,&route_planner](SDL_Event e){

        if(e.type==SDL_MOUSEBUTTONUP){

            if(e.button.button==1){
                auto dimension=display.dimensions();
                route_planner.setstart(e.button.x*100.0/dimension.x(),(dimension.y()-e.button.y)*100.0/dimension.y());
            }
            else if(e.button.button==3){
                auto dimension=display.dimensions();
                route_planner.setend(e.button.x*100.0/dimension.x(),(dimension.y()-e.button.y)*100.0/dimension.y());
            }

        }
    }));


    display.begin_show();
}
