#sginclude "://shaders/common.vert.inc" //Absoluten Pfad angeben welche Datei inkludiert werden soll, relativ wenn shader nicht in qrc

void main()
{
        gl_Position = projectionMatrix*modelViewMatrix*vertexPosition;
}
