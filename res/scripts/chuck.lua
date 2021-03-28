function on_create()
    chuck_being_hit = true
    chuck_count_hits = 45
    chuck_life = 3
    level_chuck = game_get_current_level()
    chuck = level_get_entities(level_chuck)[64]
    c_pescado_1 = level_get_entities(level_chuck)[65]
    c_pescado_2 = level_get_entities(level_chuck)[66]
    c_pescado_3 = level_get_entities(level_chuck)[67]
    chuck_sprite_attribute = entity_get_attribute(chuck,"sprite")
    chuck_music_component = entity_get_component(chuck,"music")
    chuck_damage_sprite = game_find_sprite("chuck_damage")
    chuck_burping_sprite = game_find_sprite("chuck_burp")
    chuck_izq_sprite = game_find_sprite("chuck_izq")
    chuck_der_sprite = game_find_sprite("chuck_der")
    chuck_idle_sprite = game_find_sprite("chuck_idle")
    chuck_vomitando = false
    chuck_status = -1
    chuck_vomitando1 = false
    pescado_a_tirar = 1
    listo_pescado_1 = false
    listo_pescado_2 = false
    listo_pescado_3 = false
    activa = false
    
end
function on_update()
    --Una vez que recibe daño
    if chuck_being_hit then
        --Tengo que esperar a que termine la animacion de daño
        if not chuck_vomitando then
            local chuck_current_sprite = attribute_get_sprite(chuck_sprite_attribute)
            local chuck_current_sprite_index = sprite_get_current_image(chuck_current_sprite)
            print("index")
            print(chuck_current_sprite_index)
            if chuck_current_sprite_index == 2 then
                chuck_vomitando = true
                attribute_set_sprite(chuck_sprite_attribute,chuck_burping_sprite)
            end
        else
            --Tengo que vomitar 7 pescados
            local chuck_current_sprite = attribute_get_sprite(chuck_sprite_attribute)
            local chuck_current_sprite_index = sprite_get_current_image(chuck_current_sprite)
            if chuck_current_sprite_index == 3 then
                if not activa then
                    component_music_stop_track(chuck_music_component)
                    component_music_play_track(chuck_music_component,false)
                    --Tengo que lanzar el pescado
                    local obj_pescado = nil
                    if pescado_a_tirar == 1 then
                        obj_pescado = c_pescado_1
                        listo_pescado_1 = true
                        local current_chuck_position = entity_get_position(chuck)
                        entity_set_position(c_pescado_1,current_chuck_position[1],current_chuck_position[2],current_chuck_position[3])
                    elseif pescado_a_tirar == 2 then
                        obj_pescado = c_pescado_2
                        listo_pescado_2 = true
                        local current_chuck_position = entity_get_position(chuck)
                        entity_set_position(c_pescado_2,current_chuck_position[1],current_chuck_position[2],current_chuck_position[3])
                    elseif pescado_a_tirar == 3 then
                        obj_pescado = c_pescado_3
                        listo_pescado_3 = true
                        local current_chuck_position = entity_get_position(chuck)
                        entity_set_position(c_pescado_3,current_chuck_position[1],current_chuck_position[2],current_chuck_position[3])
                        chuck_vomitando = false
                        chuck_being_hit = false
                    end
                    pescado_a_tirar = pescado_a_tirar +1
                    activa = true
                end
                
            else
                activa = false
                --print("Entre al else final")
                
            end
        end
        

    else
        attribute_set_sprite(chuck_sprite_attribute,chuck_izq_sprite)
    end
    local deltaTime = game_get_delta_time()
    if listo_pescado_1 then
        print("entre aca")
        entity_translate(c_pescado_1, -5*20*deltaTime,-4*20*deltaTime,0.0)
    end
    if listo_pescado_2 then
        entity_translate(c_pescado_2, -10*20*deltaTime,-4*20*deltaTime,0.0)
    end
    if listo_pescado_3 then
        entity_translate(c_pescado_3, -15*20*deltaTime,-4*20*deltaTime,0.0)
    end

    local fpos1 = entity_get_position(c_pescado_1)
    if fpos1[2] < -300.0 then
        listo_pescado_1 = false
    end
    local fpos2 = entity_get_position(c_pescado_2)
    if fpos2[2] < -300.0 then
        listo_pescado_2 = false
    end
    local fpos3 = entity_get_position(c_pescado_3)
    if fpos3[2] < -300.0 then
        listo_pescado_3 = false
    end
end
function on_collision(other)
    local entity_name = entity_get_name(other)
    if entity_name == "caja" then
        if not chuck_being_hit then
            
            if chuck_count_hits == 0 then
                --component_music_play_track(bird_music_component,false)
                chuck_being_hit = true
                attribute_set_sprite(chuck_sprite_attribute,chuck_damage_sprite)
                chuck_life = chuck_life -1
            else
                chuck_count_hits = chuck_count_hits-1
            end
        end
    end
end