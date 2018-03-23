module RogueLike
  module Components
    class Room
      attr_reader :width, :height

      TILES = {
        door: '+',
        floor: '.',
        top_bottom_walls: '-',
        side_walls: '|'
      }.freeze

      # TODO: needs x, y coordinates for World Map
      def initialize(width:, height:)
        @width = width
        @height = height
        @room = set_room
      end

      def get(x:, y:)
        @room[y][x]
      end

      def set(x:, y:, tile:)
        @room[y][x] = tile
      end

      def create
        @room.each_with_index do |row, y|
          row.each_with_index do |column, x|
            if (y == 0) || (y == height - 1)
              set(x: x, y: y, tile: "-")
            elsif (x == 0) || (x == width - 1)
              set(x: x, y: y, tile: "|")
            else
              set(x: x, y: y, tile: ".")
            end
          end
        end

        @room
      end

      private
        def set_room
          Array.new(height) do
            Array.new(width)
          end
        end
    end
  end
end
