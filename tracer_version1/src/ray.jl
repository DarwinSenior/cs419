module ray

    importall vec3
    import camera: Camera
    import Base: start, done, next
    export Ray, Screen, start, done, next

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
    """
    type Screen
        cam::Camera
        focus::Float64
        height::Float64
        width::Float64
    end
    
    """
    This is the uniform ray iterator, for output which primary ray to shoot
    """
    type PrimaryRayIterator
        right::Vec3f
        up::Vec3f
        origin::Vec3f
        center::Vec3f
        dx::Float64
        dy::Float64
        x_range::Int64
        y_range::Int64
        ray::Ray
    end

    start(iter::PrimaryRayIterator) = (-iter.x_range, -iter.y_range)
    function next(iter::PrimaryRayIterator, state::Tuple{Float64, Float64})
        x,y,ray = state
        y += 1
        if y > iter.y_range
            x += 1
            y = -iter.y_range
        end
        iter.ray.origin = iter.center+x*iter.dx*iter.right+y*iter.dy*iter.up
        iter.ray.dir = normalise(iter.ray.dir)
        return (iter.ray, (x,y))
    end
    done(iter::PrimaryRayIterator, state::Tuple{Float64, Float64}) = state[0]>iter.x_range
    
    # uniformRays(screen::Screen, ) = PrimaryRayIterator()

end
