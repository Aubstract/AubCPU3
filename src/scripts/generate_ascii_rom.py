import mcschematic as mcschem
from datetime import datetime


def get_char_set_pixel_data(char_set: mcschem.MCSchematic) -> list[list[bool]]:
    pixel_data = []  # an array of 2d pixel maps (3x5 pixels per char)

    origin_x = 0
    origin_y = -1
    origin_z = 0

    for character in range(96):
        char_data = []

        char_origin_x = origin_x
        char_origin_y = origin_y - ((character // 16) * 12)
        char_origin_z = origin_z - ((character % 16) * 8)

        for pix_index in range(15):
            coord_x = char_origin_x
            coord_y = char_origin_y - ((pix_index % 5) * 2)
            coord_z = char_origin_z - ((pix_index // 5) * 2)

            block_data = char_set.getBlockDataAt((coord_x, coord_y, coord_z))
            lit = block_data.find("lit=true") != -1
            char_data.append(lit)

        pixel_data.append(char_data)

    return pixel_data


def generate_ascii_rom(ascii_rom: mcschem.MCSchematic, char_pixel_data: list[list[bool]]):
    # Offset from players feet to the first barrel
    origin_x = 2
    origin_y = -1
    origin_z = 0

    for character_index, character in enumerate(char_pixel_data):
        char_origin_x = (origin_x +
                         ((character_index // 4) * 2) +  # creates rows of 4
                         ((character_index // 8) * 2))   # adds an extra space every 2 rows
        char_origin_y = origin_y
        char_origin_z = (origin_z +
                         ((character_index % 4) * 2))    # spaces barrels out every other block in a row

        for pixel_index, pixel in enumerate(character):
            coord_x = char_origin_x
            coord_y = char_origin_y - (pixel_index * 2)  # each barrel is 2 blocks lower than the previous
            coord_z = char_origin_z

            if pixel_index >= 8:
                coord_y -= 1  # 1 block lower
                coord_x -= 1 + (-2 * ((character_index // 4) % 2))  # alternative offset of second byte (forward/back)
                # This just hardcodes the z offset of the two bytes, easier than finding an algorithm
                if character_index % 4 == 0:
                    coord_z += 6
                elif character_index % 4 == 1:
                    coord_z += 2
                elif character_index % 4 == 2:
                    coord_z -= 2
                elif character_index % 4 == 3:
                    coord_z -= 6

            if pixel_index < 5:
                coord_y -= 6  # vertical offset for first 5 pixels
            elif pixel_index < 8:
                coord_y += 10  # vertical offset for next 3 pixels
            elif pixel_index < 10:
                coord_y += 6  # vertical offset for next 2 pixels
            else:
                coord_y += 20  # vertical offset for last 5 pixels

            # CORRECT THE DIRECTION BECAUSE I DOOFED UP
            coord_x *= -1
            coord_z *= -1

            ascii_rom.setBlock((coord_x, coord_y, coord_z),
                               mcschem.BlockDataDB.BARREL.fromSS(pixel))

    # Construct the sign's NBT data
    now = datetime.now()
    line1 = "ASCII Char ROM"
    line2 = "Generated:"
    line3 = now.strftime("%Y-%m-%d")
    line4 = f"""{now.strftime("%H:%M:%S")}"""
    block_data = ("""minecraft:birch_sign[rotation=8,waterlogged=false]"""
                  + """{GlowingText: 0b, Color: "black", Text4: '{"text":" """
                  + line4 + """ "}', Text3: '{"text":" """
                  + line3 + """ "}', Text2: '{"text":" """
                  + line2 + """ "}', Text1: '{"text":" """
                  + line1 + """ "}'}""")
    ascii_rom.setBlock((0, 0, 0), block_data)

    ascii_rom.save("C:/Users/Ben/AppData/Roaming/.minecraft/config/worldedit/schematics",
                   "ascii_char_rom", mcschem.Version.JE_1_18_2)


def main():
    char_set = mcschem.MCSchematic("C:/Users/Ben/AppData/Roaming/.minecraft/config/worldedit/schematics/char_set.schem")
    ascii_rom = mcschem.MCSchematic()

    char_pixel_data = get_char_set_pixel_data(char_set)
    generate_ascii_rom(ascii_rom, char_pixel_data)

    ascii_rom.save("C:/Users/Ben/AppData/Roaming/.minecraft/config/worldedit/schematics",
                   "ascii_char_rom", mcschem.Version.JE_1_18_2)


if __name__ == "__main__":
    main()
