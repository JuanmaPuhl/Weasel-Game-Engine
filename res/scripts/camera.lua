function on_create()
end
function on_update()
    
    local ent_pos = entity_get_position(entity)
    local camera_pos = entity_get_position(camera)
    fondo_pos = entity_get_position(fondo)
    local aux = (camera_pos[2]-360.0) - ent_pos[2]
    local aux2 = (camera_pos[1]-640.0) - ent_pos[1]
    val = abs(aux)
    val2 = abs(aux2)
    print(val)
    if val > 1.0 then
        entity_set_position(camera, camera_pos[1],ent_pos[2],camera_pos[3])
        entity_set_position(fondo, fondo_pos[1], ent_pos[2],fondo_pos[3])
        camera_zoom = component_camera_get_zoom(camera)
        entity_translate(camera,0.0,188.5,0.0)
        entity_translate(fondo,0.0,10.0,0.0)
        camera_pos = entity_get_position(camera)
        component_camera_move(component_camera,camera_pos[1],camera_pos[2],camera_pos[3])
    end
    if val2 > 1.0 then
        camera_pos = entity_get_position(camera)
        camera_zoom = component_camera_get_zoom(camera)
        fondo_pos = entity_get_position(fondo)
        entity_set_position(camera, ent_pos[1],camera_pos[2],camera_pos[3]);
        entity_set_position(fondo, ent_pos[1], fondo_pos[2],fondo_pos[3])
        entity_translate(camera,300,0.0,0.0)
        --entity_translate(fondo,100,0.0,0.0)
        camera_pos = entity_get_position(camera)
        print(camera_pos[1] - 600.0)
        if camera_pos[1] - 600.0 <= -2853.0 then
            print("Entre")
            entity_translate(camera,200.0,0.0,0.0)
            entity_translate(fondo,200.0,0.0,0.0)
        end
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