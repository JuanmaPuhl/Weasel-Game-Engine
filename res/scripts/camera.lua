function on_create()
end
function on_update()
    
    local ent_pos = entity_get_position(entity)
    local camera_pos = entity_get_position(camera)
    local aux = (camera_pos[2]-360.0) - ent_pos[2]
    local aux2 = (camera_pos[1]-640.0) - ent_pos[1]
    val = abs(aux)
    val2 = abs(aux2)
    print(val)
    if val > 1.0 then
        entity_set_position(camera, camera_pos[1],ent_pos[2],camera_pos[3]);
        entity_translate(camera,0.0,360.0,0.0)
        camera_pos = entity_get_position(camera)
        component_camera_move(component_camera,camera_pos[1],camera_pos[2],camera_pos[3])
    end
    if val2 > 1.0 then
        camera_pos = entity_get_position(camera)
        entity_set_position(camera, ent_pos[1],camera_pos[2],camera_pos[3]);
        entity_translate(camera,640.0,0.0,0.0)
        camera_pos = entity_get_position(camera)
        component_camera_move(component_camera,camera_pos[1],camera_pos[2],camera_pos[3])
    end
end
function on_collision()
end

function abs(number)
    if number > 1.0 then
        return number
    else
        return -1 * number
    end
end