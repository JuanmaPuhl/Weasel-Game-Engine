function on_create()
    chuck_being_hit = false
    chuck_count_hits = 45
    chuck_life = 3
    level_chuck = game_get_current_level()
    chuck = level_get_entities(level_chuck)[64]
    c_pescado_1 = level_get_entities(level_chuck)[65]
    c_pescado_2 = level_get_entities(level_chuck)[66]
    c_pescado_3 = level_get_entities(level_chuck)[67]
    iman = level_get_entities(level_chuck)[70]
    iman2 = level_get_entities(level_chuck)[82]
    basurita = level_get_entities(level_chuck)[68]
    caja = level_get_entities(level_chuck)[71]
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
    chuck_activated = false
    chuck_periodo_gracia = 350
    traer_iman = false
    traer_basura = false
    traer_caja = true
    recuperar_iman = false
    recuperar_iman2 = false
    tirar_basura = false
    basurita_vspeed = 0.0
    caja_vspeed = 0.0
    tirar_caja = false

    chuck_ready = false
    chuck_fin = false
    
end
function on_update()
    if chuck_life == 0 and not chuck_ready then
        chuck_activated = false
        chuck_ready = true
        attribute_set_sprite(chuck_sprite_attribute,bin_explosion_sprite)
        component_music_play_track(bin_music_component,false)
    end
    if chuck_ready and not chuck_fin then
        local curr_spr = attribute_get_sprite(chuck_sprite_attribute)
        local curr_index = sprite_get_current_image(curr_spr)
        if curr_index == 6 then
            entity_set_position(chuck,10000,10000,10000)
            chuck_fin = true
        end
    end
    if chuck_activated then

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
                            traer_caja = true
                            subir = false
                            caja_activada = false
                            entity_set_position(caja,2771.0,17.0,0.0)
                        end
                        pescado_a_tirar = pescado_a_tirar +1
                        if pescado_a_tirar>3 then pescado_a_tirar = 1 end
                        activa = true
                    end
                    
                else
                    activa = false
                    --print("Entre al else final")
                    
                end
            end
        else --Si no está dañado
            attribute_set_sprite(chuck_sprite_attribute,chuck_idle_sprite)
            
        end
        --En todo momento
        local deltaTime = game_get_delta_time()
        print(chuck_periodo_gracia)
        if chuck_periodo_gracia <= 0 and not traer_iman and not traer_basura and not recuperar_iman and not chuck_being_hit then --Tiene que atacar
            attribute_set_sprite(chuck_sprite_attribute,chuck_izq_sprite)
            traer_iman = true
            traer_basura = true
            basurita_vspeed = 0.0
            tirar_basura = false
            entity_set_position(basurita,2771.0,21.0,0.0)
            chuck_periodo_gracia = 350 -- lo reseteo
        else
            chuck_periodo_gracia = chuck_periodo_gracia - 1 
        end

        if recuperar_iman then
            --attribute_set_sprite(chuck_sprite_attribute,chuck_der_sprite)
            local iman_position = entity_get_position(iman)
            print("Posicion iman")
            print(iman_position[1])
            if iman_position[1] >= 2770.0 then
                recuperar_iman = false
                entity_translate(iman,-2.0,0.0,0.0)
            else
                entity_translate(iman,60*deltaTime,0.0,0.0)
            end
        end
        if traer_iman then
            --Avanzo a la izquierda hasta llegar a la pos del jugador
            local player_position = entity_get_position(entity)
            local iman_position = entity_get_position(iman)
            if iman_position[1] <= player_position[1] then
                traer_iman = false
                traer_basura = false
                recuperar_iman = true
                tirar_basura = true
            else
                entity_translate(iman,-60*deltaTime,0.0,0.0)
                entity_translate(basurita,-60*deltaTime,0.0,0.0)
            end
        end

        if tirar_basura then
            entity_translate(basurita,0.0, basurita_vspeed * deltaTime,0.0)
            basurita_vspeed = basurita_vspeed - 5.6
        end

        if recuperar_iman2 then
            --attribute_set_sprite(chuck_sprite_attribute,chuck_der_sprite)
            local iman_position2 = entity_get_position(iman2)
            print("Posicion iman2")
            print(iman_position2[1])
            if iman_position2[1] >= 2770.0 then
                recuperar_iman2 = false
                entity_translate(iman2,-2.0,0.0,0.0)
            else
                entity_translate(iman2,60*deltaTime,0.0,0.0)
            end
        end

        if traer_caja then
            local iman_position2 = entity_get_position(iman2)
            if iman_position2[1] <= 2591.0 then
                traer_caja = false
                recuperar_iman2 = true
                tirar_caja = true
                
            else
                entity_translate(iman2,-60*deltaTime,0.0,0.0)
                entity_translate(caja,-60*deltaTime,0.0,0.0)
            end
        end

        if tirar_caja then
            local caja_position = entity_get_position(caja)
            if caja_position[2] <= -86.0 then
                tirar_caja = false
                vspeed_cajita = 0.0
            end
            entity_translate(caja,0.0, caja_vspeed * deltaTime,0.0)
            caja_vspeed = caja_vspeed - 5.6
        end


        --Se actualizan las posiciones de los pescados
        
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
    
end
function on_collision(other)
    local entity_name = entity_get_name(other)
    if entity_name == "caja" then
        print("HUBO COLISION")
        if not chuck_being_hit and caja_activada then
            --component_music_play_track(bird_music_component,false)
            chuck_being_hit = true
            attribute_set_sprite(chuck_sprite_attribute,chuck_damage_sprite)
            chuck_life = chuck_life -1
            caja_activada = false
        end
    end
end