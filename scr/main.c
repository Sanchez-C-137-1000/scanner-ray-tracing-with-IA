#include <stdio.h>
#include <stdlib.h>
#include "point_cloud.h"
#include "serial_reader.h"
#include "render_engine.h"

int main() {
    PointCloud cloud;
    pointcloud_init(&cloud);
    
    // Inicializar renderizado (800x600)
    render_init(800, 600);
    
    // Configurar puerto serial (ajustar según SO)
    serial_init("/dev/ttyACM0"); // Linux
    // serial_init("COM3");      // Windows
    
    char buffer[256];
    while(1) {
        if(serial_read_line(buffer, sizeof(buffer))) {
            if(strcmp(buffer, "FIN") == 0) {
                printf("Escaneo completado\n");
                break;
            }
            process_scan_data(buffer, &cloud);
            
            // Renderizar cada 100 puntos
            if(cloud.count % 100 == 0) {
                render_frame(&cloud);
            }
        }
    }
    
    // Renderizar resultado final
    render_frame(&cloud);
    
    render_cleanup();
    return 0;
}
