from pytmx.util_pygame import load_pygame
from pytmx import TiledMap, TiledTileset, TiledObjectGroup, TiledObject, TiledTileLayer
from pathlib import Path
import shutil
import struct
import pygame


MAPS_DIR = Path("../src/resources/data/maps")


def load_map(map_path: Path) -> None:
    m: TiledMap = load_pygame(map_path)
    
    path = Path(f"../src/resources/data/maps/{map_path.stem}.bin")
    file = open(path, "wb")
    
    for obj_group in m.layers:
        if (isinstance(obj_group, TiledObjectGroup) is False):
            continue        
        obj_group: TiledObjectGroup
        obj_list: list[TiledObject] = [x for x in obj_group]
        file.write(struct.pack('i', obj_group.properties['group-id']))
        file.write(struct.pack('i', len(obj_list)))
        
        for obj in obj_list:
            file.write(struct.pack('f', obj.x))
            file.write(struct.pack('f', obj.y))
            file.write(struct.pack('f', obj.width))
            file.write(struct.pack('f', obj.height))
            if (obj.properties.get('source')):
                s: str = obj.properties.get('source').replace("../tilesets\../..", "./resources")
                s += '\0'
                file.write(bytes(s, "ASCII"))
    
    file.close()
    shutil.copy(path, Path(f"tmp/{map_path.stem}.bin"))
    

def main() -> None:
    d = pygame.display.set_mode((100, 100))
    for file in MAPS_DIR.iterdir():
        if file.suffix == ".tmx":
            load_map(file)


if __name__ == "__main__":
    main()