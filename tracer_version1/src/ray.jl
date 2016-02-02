module ray

    importall vec3
    import camera: Camera
    import Base: start, done, next
    export Ray, Screen, shootRay

    type Ray
        origin::Vec3f
        dir::Vec3f
    end
    Ray() = Ray(Vec3f(0, 0, 0), Vec3f(0, 0, 1))

    """
    A screen is somewhate similar to pinhole mode except the screen is in front of the camera
    rather than behind it
    focus is the distance from camera to screen
    height is screen's height
    width is screen's width
    if the foucus is finitly far away (inf, it becomes the othographic ray tracer)
    """
    type Screen
        focus::Float64
        height::Float64
        width::Float64
    end

    function setOrthorgraphic(screen::Screen)
        screen.focus = Inf
    end

    function rayPos(screen::Screen, cam::Camera, x::Float64, y::Float64)
        """
        helper function, used to generate the perspective ray and orthographic ray shooting position
        """
        x = x-0.5
        y = y-0.5
        origin = cam.pos
        dx = cross(cam.up, cam.front)
        dy = cam.up
        origin = origin + (x*screen.width/2)*dx + (y*screen.height/2)*dy
        return origin
    end

    function shootRay(screen::Screen, cam::Camera, x::Float64, y::Float64)
        camera.focus == Inf ? orthographicRay(screen, cam, x, y) : perspectiveRay(screen, cam, x, y)
    end

    function perspectiveRay(screen::Screen, cam::Camera, x::Float64, y::Float64)
        """
        given screen, cam and (x,y) ratio of the camera, output the ray from perspective projection
        """
        pos = rayPos(screen, cam, x, y)
        dir = normalise(pos - cam.pos - focus * cam.front)
        return Ray(pos, dir)
    end


    function orthographicRay(screen::Screen, cam::Camera, x::Float64, y::Float64)
        """
        given screen, cam and (x,y) ratio of the camera, output the ray from othographic projection
        """
        pos = rayPos(screen, cam, x, y)
        dir = cam.front
        return Ray(pos, dir)
    end

end
