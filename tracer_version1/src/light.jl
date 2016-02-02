module light
import Vec3f

type Light
    pos::Vec3f
    dir::Vec3f
end


function intensity(light::Light, height::Height)
