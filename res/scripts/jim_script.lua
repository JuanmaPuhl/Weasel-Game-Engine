function on_create()
    print("JIM::OnCreate")
    gravity = -9.8
    vspeed = 0
    falling = true
    disparando = false
    status = 1
    count = 1
    walking = false
    prueba = "Esto es una prueba"
    level = game_get_current_level()
    entities = level_get_entities(level)
    sprite_idle = game_find_sprite("idle")
    sprite_walking = game_find_sprite("walking")
    sprite_shooting = game_find_sprite("shooting")
    sprite_ducking = game_find_sprite("ducking")
    jumping1 = game_find_sprite("jumping1")
    jumping2 = game_find_sprite("jumping2")
    jumping3 = game_find_sprite("jumping3")
    sprite_clinging = game_find_sprite("clinging")
    sprite_walking_clinging = game_find_sprite("walking_clinging")
    walking_clinging = false
    clinging = false
    ducking_speed = sprite_get_speed(sprite_ducking)
    print(ducking_speed)
    ducking = false
    print(sprite_idle)
    print(sprite_walking)
    local count = 0
    print("llegue")
    camera = level_get_camera(level)
    component_camera = entity_get_component(camera,"camera")
    e_pos = component_camera_get_position(component_camera)
    print(e_pos[1])
    entity_set_position(camera,e_pos[1],e_pos[2], e_pos[3])
    for _ in pairs(entities) do count = count + 1 end
    if count >= 3 then
        entity = entities[1]
        fire = entities[2]
        fondo = entities[3]
        print("llegue")
        sprite_attribute = entity_get_attribute(entity,"sprite")
        fire_attr = entity_get_attribute(fire, "sprite")
        sprite_fire = attribute_get_sprite(fire_attr)
        col_attr = entity_get_attribute(entity,"color")
        music_component = entity_get_component(entity, "music1");
        print(sprite_attribute)
        print(fire_attr)

        sprite_set_transparency(sprite_fire,0.0)
        collision = false
        
    end
    log_print("Esto es una prueba desde LUA")
end

function on_update()
    if(entity ~= nil and fire ~= nil ) then
        if collision then
            attribute_set_color(col_attr,1.0,0.0,0.0,0.0)
        end
        local deltaTime = game_get_delta_time()
        local speed = 96.0
        if falling then
            entity_translate(entity,0.0, vspeed * deltaTime,0.0)
            vspeed = vspeed + gravity
        end
        if is_pressed(KEY_RIGHT) then
            if not clinging then
                falling = true
                if not walking then
                    attribute_set_sprite(sprite_attribute, sprite_walking)
                    walking = true
                end
                if status == -1 then
                    status = 1
                    entity_scale(entity, -1.0,1.0,1.0)
                    entity_set_position(fire, 0.0,0.0,0.0)
                    entity_scale(fire, -1.0,1.0,1.0)
                end
                entity_translate(entity, speed * deltaTime,0.0,0.0)
                entity_translate(camera, speed * deltaTime,0.0,0.0);
                entity_translate(fondo, speed * deltaTime,0.0,0.0);
                local camera_pos = entity_get_position(camera)
                component_camera_move(component_camera,camera_pos[1],camera_pos[2],camera_pos[3])
            else
                if not walking_clinging then
                    attribute_set_sprite(sprite_attribute, sprite_walking_clinging)
                    walking_clinging = true
                end
                if status == -1 then
                    status = 1
                    entity_scale(entity, -1.0,1.0,1.0)
                    entity_set_position(fire, 0.0,0.0,0.0)
                    entity_scale(fire, -1.0,1.0,1.0)
                end
                    entity_translate(entity,speed * deltaTime,0.0,0.0)
                    entity_translate(camera, speed * deltaTime,0.0,0.0);
                    entity_translate(fondo, speed * deltaTime,0.0,0.0);
                    local camera_pos = entity_get_position(camera)
                    component_camera_move(component_camera,camera_pos[1],camera_pos[2],camera_pos[3])
            end
        end
        if is_pressed(KEY_LEFT) then
            if not clinging then
                falling = true
                if not walking then
                    attribute_set_sprite(sprite_attribute, sprite_walking)
                    walking = true
                end
                if status == 1 then
                    status = -1
                    entity_scale(entity, -1.0,1.0,1.0)
                    entity_set_position(fire, 0.0,0.0,0.0)
                    entity_scale(fire, -1.0,1.0,1.0)
                end
                entity_translate(entity,-speed * deltaTime,0.0,0.0)
                entity_translate(camera, -speed * deltaTime,0.0,0.0);
                entity_translate(fondo, -speed * deltaTime,0.0,0.0);
                local camera_pos = entity_get_position(camera)
                component_camera_move(component_camera,camera_pos[1],camera_pos[2],camera_pos[3])
            else
                if not walking_clinging then
                    attribute_set_sprite(sprite_attribute, sprite_walking_clinging)
                    walking_clinging = true
                end
                if status == 1 then
                    status = -1
                    entity_scale(entity, -1.0,1.0,1.0)
                    entity_set_position(fire, 0.0,0.0,0.0)
                    entity_scale(fire, -1.0,1.0,1.0)
                end
                    entity_translate(entity,-speed * deltaTime,0.0,0.0)
                    entity_translate(camera, -speed * deltaTime,0.0,0.0);
                    entity_translate(fondo, -speed * deltaTime,0.0,0.0);
                    local camera_pos = entity_get_position(camera)
                    component_camera_move(component_camera,camera_pos[1],camera_pos[2],camera_pos[3])
            end
        end
        if is_pressed(KEY_UP) then
            --[[ entity_translate(entity,0.0,speed * deltaTime,0.0)
            entity_translate(camera,0.0, speed * deltaTime,0.0);
            entity_translate(fondo,0.0, speed * deltaTime,0.0);
            local camera_pos = entity_get_position(camera)
            component_camera_move(component_camera,camera_pos[1],camera_pos[2],camera_pos[3]) ]]
        end
        if is_pressed(KEY_DOWN) then
            if not clinging then
                if not ducking then
                    sprite_set_speed(sprite_ducking,ducking_speed)
                    sprite_restart(sprite_ducking)
                    --Cambio el sprite a ducking
                    attribute_set_sprite(sprite_attribute,sprite_ducking)
                    --seteo ducking true
                    ducking = true
                else
                    index_ducking = sprite_get_current_image(sprite_ducking)
                    if index_ducking == 3 then
                        sprite_set_speed(sprite_ducking,0.0)
                    end
                end
            end
            
--[[             entity_translate(entity,0.0,-speed * deltaTime,0.0)
            entity_translate(fondo,0.0, -speed * deltaTime,0.0);
            entity_translate(camera,0.0, -speed * deltaTime,0.0);
            local camera_pos = entity_get_position(camera)
            component_camera_move(component_camera,camera_pos[1],camera_pos[2],camera_pos[3])
 ]]      end
        if not is_pressed(KEY_RIGHT) and not is_pressed(KEY_LEFT) and not is_pressed(KEY_Z) and not is_pressed(KEY_DOWN) then
            if not falling and not walking then
                attribute_set_sprite(sprite_attribute, sprite_idle)
            end
            if walking then
                walking = false
                attribute_set_sprite(sprite_attribute, sprite_idle)
            end
            if disparando then
                print("disparando")
                disparando = false
                attribute_set_sprite(sprite_attribute, sprite_idle)
            end
            if ducking then
                ducking = false
                attribute_set_sprite(sprite_attribute, sprite_idle)
                sprite_set_speed(sprite_ducking,11.4)
                sprite_restart(sprite_ducking)
            end
            if clinging and not walking_clinging then
                attribute_set_sprite(sprite_attribute, sprite_clinging)
            end
            if clinging and walking_clinging then
                walking_clinging = false
                attribute_set_sprite(sprite_attribute, sprite_clinging)
            end
            
        end
        if is_pressed(KEY_Z) then
            if not disparando then
                component_music_set_track(music_component, "res/audio/disparo.wav")
                print("la direccion es: ")
                component_music_get_track(music_component)
                component_music_play_track(music_component,true)
                --print(track)
                
                sprite_set_transparency(sprite_fire,1.0)
                disparando = true
                attribute_set_sprite(sprite_attribute, sprite_shooting)
            end
            
            pos = entity_get_position(entity)
            entity_set_position(fire, pos[1] + status * 36.0, pos[2] + 15.0, pos[3])
        else
            disparando = false
            component_music_stop_track(music_component)
            sprite_set_transparency(sprite_fire,0.0)
    
        end
        if is_pressed(KEY_C) and not falling then
            print("C")
            vspeed = 500
            attribute_set_sprite(sprite_attribute,jumping1)
            clinging = false
            --entity_translate(entity, 0.0,100.0,0.0 )
            falling = true
        end
        if vspeed < 200  and vspeed>0 then
            attribute_set_sprite(sprite_attribute,jumping2)
        end
        if vspeed < 0 and not walking then 
            attribute_set_sprite(sprite_attribute, jumping3)
        end
        --[[ if vspeed == 0 and not is_pressed(KEY_RIGHT) and not is_pressed(KEY_LEFT) and not is_pressed(KEY_Z) and not is_pressed(KEY_DOWN) then
            attribute_set_sprite(sprite_attribute, sprite_idle)
        end ]]
    end
    
    

end

function on_collision(other)
    local entity_name = entity_get_name(other)
    --collision = true
    --print(entity_name)
    if entity_name == "floor" then
        if falling then
            falling = false
            local collision_position = entity_get_position(other)
            local entiy_pos = entity_get_position(entity)
            entity_translate(entity,0,1,0)
            vspeed = 0
        end
    end
    if entity_name == "bird" then
        print("BIRD")
    end
    --print(entity_name)
    if entity_name == "rope" then
        if not clinging then
            clinging = true
            vspeed = 0
            local collision_position = entity_get_position(other)
            local entiy_pos = entity_get_position(entity)
            print(clinging)
            --entity_translate(entity,0,-1,0)
            falling = false
        end
    end
    if entity_name == "rebote" then
        attribute_set_sprite(sprite_attribute,jumping1)
        vspeed = 500
        falling = true
    end
    --vspeed = 0
end