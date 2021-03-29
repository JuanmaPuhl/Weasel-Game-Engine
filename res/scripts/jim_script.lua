function on_create()
    print("JIM::OnCreate")
    gravity = -9.8
    vspeed = 0
    falling = true
    disparando = false
    jefe_final = false
    status = 1
    count = 1
    walking = false
    trepando = false
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
    animacion_final = game_find_sprite("jim_ending")
    climbing_sprite = game_find_sprite("climbing")
    sprite_clinging = game_find_sprite("clinging")
    sprite_walking_clinging = game_find_sprite("walking_clinging")
    damage_sprite = game_find_sprite("jim_damage")
    walking_clinging = false
    clinging = false
    ducking_speed = sprite_get_speed(sprite_ducking)
    jim_being_hurt = false
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
        music_component = entity_get_component(entity, "music1")
        rebote_music_component = entity_get_component(entity, "music2")
        inodoro_music_component = entity_get_component(entity, "music3")
        damage_music_component = entity_get_component(entity, "music4")
        print(sprite_attribute)
        print(fire_attr)

        sprite_set_transparency(sprite_fire,0.0)
        collision = false
        disparo_collider = entities[56]

    end
    log_print("Esto es una prueba desde LUA")
    seteada_animacion = false
    seteada_musica = false
    finalizar_juego = false
end

function on_update()
    if chuck_fin then
        if finalizar_juego then
            game_set_current_level(1)
        else
            if not seteada_animacion then 
                attribute_set_sprite(sprite_attribute, animacion_final)
                seteada_animacion = true
            end
            local sp = attribute_get_sprite(sprite_attribute)
            local curr_sprite = sprite_get_current_image(sp)
            if curr_sprite == 39 then
                if not seteada_musica then
                    seteada_musica = true
                    component_music_stop_track(entity_get_component(entity, "music"))
                    component_music_set_track(inodoro_music_component,"C:/Users/juanm/Documents/WeaselEngine/res/audio/yeejaw.wav")
                    component_music_stop_track(inodoro_music_component)
                    component_music_play_track(inodoro_music_component,false)
                    
                end
            end
            if curr_sprite >= 39 then
                entity_scale(entity,1.05,1.05,1.0)
            end
            if curr_sprite == 42 then
                finalizar_juego = true
            end
        end
    end
    if(entity ~= nil and fire ~= nil and not chuck_fin) then
        if collision then
            attribute_set_color(col_attr,1.0,0.0,0.0,0.0)
        end
        local deltaTime = game_get_delta_time()
        local speed = 96.0
        if falling then
            entity_translate(entity,0.0, vspeed * deltaTime,0.0)
            vspeed = vspeed + gravity
        end
        if jim_being_hurt then
            local sp = attribute_get_sprite(sprite_attribute)
            local curr_sprite = sprite_get_current_image(sp)
            if curr_sprite == 6 then
                jim_being_hurt = false
            end
            return 1
        end
        if trepando then
            local sp = attribute_get_sprite(sprite_attribute)
            local curr_sprite = sprite_get_current_image(sp)
            if curr_sprite == 7 then
                trepando = false
                entity_translate(entity,offset_x,offset_y,0)
                sprite_restart(climbing_sprite)
                attribute_set_sprite(sprite_attribute,sprite_idle)
                clinging = false
                walking_clinging = false
                falling = true
            end
            return 1
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
                --entity_translate(camera, speed * deltaTime,0.0,0.0);
                entity_translate(fondo, speed * deltaTime,0.0,0.0);
                --local camera_pos = entity_get_position(camera)
                --component_camera_move(component_camera,camera_pos[1],camera_pos[2],camera_pos[3])
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
                    --entity_translate(camera, speed * deltaTime,0.0,0.0);
                    entity_translate(fondo, speed * deltaTime,0.0,0.0);
                    --local camera_pos = entity_get_position(camera)
                    --component_camera_move(component_camera,camera_pos[1],camera_pos[2],camera_pos[3])
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
                --entity_translate(camera, -speed * deltaTime,0.0,0.0);
                entity_translate(fondo, -speed * deltaTime,0.0,0.0);
                --local camera_pos = entity_get_position(camera)
                --component_camera_move(component_camera,camera_pos[1],camera_pos[2],camera_pos[3])
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
                    --entity_translate(camera, -speed * deltaTime,0.0,0.0);
                    entity_translate(fondo, -speed * deltaTime,0.0,0.0);
                    --local camera_pos = entity_get_position(camera)
                    --component_camera_move(component_camera,camera_pos[1],camera_pos[2],camera_pos[3])
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
            if not moving and not clinging and not jumping and not jim_being_hurt then
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
                --Tengo que mover el collider de disparo a la posición deseada
                entity_set_position(disparo_collider, pos[1], pos[2], pos[3])
                entity_translate(disparo_collider,status * 200.0,0.0,0.0)
            end 
            
        else
            disparando = false
            entity_set_position(disparo_collider,10000.0,10000.0,20)
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
        --component_music_stop_track(rebote_music_component)
        component_music_set_volume(rebote_music_component,0.3)
        component_music_play_track(rebote_music_component,false)
        vspeed = 500
        falling = true
    end
    if entity_name == "inodoro" then
        component_music_play_track(inodoro_music_component,false)
        bin_activated = true
        entity_set_position(entity,1626.0,168.0,0.0)
    end
    if entity_name == "basura" then
        if not jim_being_hurt then
            attribute_set_sprite(sprite_attribute,damage_sprite)
            jim_being_hurt = true
            component_music_stop_track(damage_music_component)
            --component_music_set_volume(damage_music_component,0.5)
            component_music_play_track(damage_music_component,false)
        end
    end
    if entity_name == "pescado" then
        if not jim_being_hurt then
            attribute_set_sprite(sprite_attribute,damage_sprite)
            jim_being_hurt = true
            component_music_stop_track(damage_music_component)
            --component_music_set_volume(damage_music_component,0.5)
            component_music_play_track(damage_music_component,false)
        end
    end
    if entity_name == "border" then
        if not trepando then
            trepando = true
            attribute_set_sprite(sprite_attribute,climbing_sprite)
            scale = entity_get_scale(other)
            local entity_scaling = entity_get_scale(entity)
            offset_x = status * scale[1] --+ entity_scaling[1]/2
            offset_y = scale[2] --+ entity_scaling[2]
            falling = false
            vspeed = 0
            clinging = false
            walking_clinging = false
        end
    end
    if entity_name == "trigger_chuck" then
        if not chuck_activated and not jefe_final then
            chuck_activated = true
            jefe_final = true
        end
    end
    --vspeed = 0
end