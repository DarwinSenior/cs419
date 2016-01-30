module camera
    importall vec3

    export Camera, pitch!, yaw!, roll!, move! 
    @enum CameraMethod othographic=0 perspective=1
    @enum SampleMethod uniform=0 multi_jittered=1

    type Camera
        up::Vec3f # z axis
        front::Vec3f # x axis
        pos::Vec3f
    end

    Camera() = Camera(Vec3f(0,1,0), Vec3f(0,0,1), Vec3f(0,0,0))

    function move!(cam::Camera, v::Float64)
        cam.pos = cam.pos + cam.front*v 
        cam
    end
    move!{T<:Number}(cam::Camera, v::T) = move!(cam,Float64(v))

    """
    change the x axis of the camera, by v-degree (0-2pi)
    """
    function pitch!(cam::Camera, v::Float64)
        right = cross(cam.up, cam.front)
        right = normalise(cos(v)*right+sin(v)*cam.up)
        cam.up = cross(cam.front, right)
        cam
    end
    pitch!{T<:Number}(cam::Camera, v::T) = pitch!(cam,Float64(v))


    """
    change the y axis of the camera, by v-degree (0-2pi)
    """
    function yaw!(cam::Camera, v::Float64)
        right = cross(cam.up, cam.front)
        cam.up = normalise(cos(v)*cam.up+sin(v)*cam.front)
        cam.front = cross(right, cam.up)
        cam
    end
    yaw!{T<:Number}(cam::Camera, v::T) = yaw!(cam,Float64(v))

    """
    change the z axis of the camera, by v-degree (0-2pi)
    """
    function roll!(cam::Camera, v::Float64)
        right = cross(cam.up, cam.front)
        cam.front = normalise(cos(v)*cam.front+sin(v)*right)

        cam
    end
    roll!{T<:Number}(cam::Camera, v::T) = roll!(cam,Float64(v))
        
end
